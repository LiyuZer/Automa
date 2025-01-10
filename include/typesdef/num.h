#include <iostream>
#include <memory>
#include <string>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#include "../typesdef/bool.h"

/*
This is the file for defining the num type(one numbers class to control them all), because I am crazy I will make them arbitrary precision. 
Why not? Life is short, and I am not going to be the one to tell you that you can't have a 1000 digit integer lol. 
Let's go! 

We will define it using as a number of base 2^64, and store the the digits as vectors of 64 bit integers. 
Oooh this is going to be fun. 

Additionally this will be a memory container, so we will have to define the memory container for this. It will be an immutable 
type, so we will have to set the immutable flag to true. Also it will have an internal type of "int". 

Note any immutable memory container can have a type, however during runtime we check to see if a memory container 
that is not an integer is being used as an integer, if so we throw an error. Same for other literals, this way we keep some 
semblance of type safety.

Other types, go take a hike.

What will the memory container have you say? 

{
    val : an arbitrary integer struct
    type : "num"
}

For ints all operations will be implemented as part of the class, rather than a symbol pointing to a graph.
The reason being speed and efficiency, these are the most common operations and we want them to be as fast as possible.

We will implement addition, subtraction, multiplication, division, modulo, equal, not equal, less, greater, less equal, greater equal, and, or, not.

We will store in memory the digits of the integer, and the sign of the integer.
Let the games begin. 

*/
using namespace std;
class Num : public Memory{ // Kind of a cool name, I think, what would be cooler?
    private:
    vector<uint64_t> digits;
    bool negative;
    int exponent = 0;// This is the exponent bit, that will be used to store the exponent of the number in base 2^64
    int precision = 12; // The precision of the fractional, how many base 2^64 digits it can have
    public:
    Num(string integer) : Memory("num"){
        if (integer[0] == '-'){
            negative = true;
            integer = integer.substr(1);
        }
        else{
            negative = false;
        }
        convert_to_num(integer);

        // Set Memory container
        set_immutable(true);

    }
    Num(vector<uint64_t> dig, bool neg, int exp) : Memory(){
        digits = dig;
        negative = neg;
        exponent = exp;
        set_immutable(true);
    }
    int get_exponent(){
        return exponent;
    }
vector<uint64_t> long_divide_integer_base2_64(vector<uint64_t> dividend, uint64_t divisor, uint64_t& final_remainder){
    /*  
        This will take a base 2^64 integer and divide it by a divisor
        We will use a base 128 integer to store the dividend and the remainder
        When we add the partial quotient.         
    */


    uint64_t remainder = 0;
    uint64_t quotient = 0;
    vector<uint64_t> final_quotient;
    __uint128_t base_128_dividend = (__uint128_t)dividend[0];// The dividend is the first digit


    int index = 1;
    while(index <= dividend.size()){
        quotient = base_128_dividend / divisor;
        remainder = base_128_dividend % divisor;
        final_remainder = remainder; 

        if(quotient > 0){
            // We shift the remainder to the left by 64 bits and add the next digit
            
            final_quotient.push_back(quotient);
            base_128_dividend = ((__uint128_t)remainder << 64);
            if(index < dividend.size()){
                base_128_dividend += dividend[index];
            }
            index++;
            
        }
        else{
            if(remainder == 0){
                final_quotient.push_back(0);
            }
            base_128_dividend = remainder;
            if(index < dividend.size()){
                base_128_dividend = ((__uint128_t)remainder << 64) + dividend[index];
            }
            index++;
            
        }

    }
    
    if(final_quotient == vector<uint64_t>()){
        final_quotient.push_back(0);
    }
    
    return final_quotient;   
}
bool leading_zeros(string& integer, string& zero_lis){
    /* 
    This function will remove leading zeros from the integer, and update 
    zero list with zeros that were removed
    */
    int zero_count = 0;
    while(integer[0] == '0'){
        zero_count++;
        zero_lis += "0";
        integer = integer.substr(1);
    }
    if(zero_count > 0){
        return true;
    }
    return false;
}
string long_divide_power_2(string dividend, int base_2, uint64_t& final_remainder){
    /* 
     This function will divide the dividend by the divisor and return the remainder
     Power of 2 for speed and efficiency. One digit at a time currently
    */

    uint64_t remainder = 0;
    uint64_t quotient = 0;
    string final_quotient = "";
    int current_index = 0;
    string current_dividend = "";

    while(current_index < dividend.size()){

        // Add one digit at a time to the current dividend
        current_dividend += dividend[current_index];
        current_index++;

        uint64_t digit; 
        if(current_dividend == ""){
            break;
        }
        else{
            digit = stoull(current_dividend);
        }
        quotient = digit >> base_2; // Divide by base_2
        remainder = digit & (((uint64_t)1 << base_2) - 1); // Remainder is the last base_2 bits
        final_remainder = remainder;
        
        if(quotient > 0){
            // We have to store the quotient in the remainder vector 
            final_quotient += std :: to_string(quotient);
        }
        else{
            final_quotient += "0"; // Regardless of the remainder we add a zero
        }

        if(remainder > 0){
            current_dividend = std:: to_string(remainder);
        }
        else{
            current_dividend = "";
        }

    }
    // Remove any leading zeros
    while(final_quotient[0] == '0'){
        final_quotient = final_quotient.substr(1);
    }

    if(final_quotient == ""){
        final_quotient = "0";
    }
    
    return final_quotient;   
}

    int get_precision(){
        return precision;
    }
    string multiply_by_power_of_2_for_decimal(string num, int base_2, uint64_t& final_digit){
    /* 
        Multiply the number by a power of 2, same as long division 
        except this function is used for multiplication, specifically 
        for decimal numbers. We will multiply the number by a power of 2
        and then store the digit before the decimal point in the digit variable. 

        As the number can be arbitrary precision, what we will do is take each digit of the number 
        multiply it by the power of 2 and then add them all together, obviously we will have to 
        shift each product, by a factor of 10 then add them one by one. 
    */

        uint64_t digit = 0;
        vector<string> intermediate_products;
        string final_product = "";

        int cn = 0;
        for(int i = num.size() - 1; i >= 0; i--){
            // Add I number of zeros to the end of the number
            digit = (uint64_t)(num[i] - '0') << base_2;
            string zeros = "";
            for(int j = 0; j < cn; j++){
                zeros += "0";
            }
            intermediate_products.push_back(std::to_string(digit) + zeros);// Really slow, but we will optimize later
            cn += 1;
        }
        /*  
            Now we will add the intermediate products together
        */
        // Get the maximum length of the intermediate products
        int max_length = 0;
        for(auto product : intermediate_products){
            if(product.size() > max_length){
                max_length = product.size();
            }
        }
        // Add zeros to the beginning of the products
        for(int i = 0; i < intermediate_products.size(); i++){
            string zeros = "";
            for(int j = 0; j < max_length - intermediate_products[i].size(); j++){
                zeros += "0";
            }
            intermediate_products[i] = zeros + intermediate_products[i];
        }

        // Now we will add the products together
        uint64_t carry = 0; 

        // We will start with the least significant digit
        for(int i = max_length - 1; i >= 0; i--){
            uint64_t sum = 0;
            for(auto product : intermediate_products){
                sum += product[i] - '0';
            }
            sum += carry;
            carry = sum / 10;
            final_product = std::to_string(sum % 10) + final_product;
        }
        if(carry > 0){
            final_product = std::to_string(carry) + final_product;
        }
        // final digit are the digits before the decimal point, take the 
        // original numbers size, take those many of the last digits of the final product

        string final_digit_str = final_product.substr(0, final_product.size() - num.size());
        if (final_digit_str != ""){
            final_digit = stoull(final_digit_str);
        }
        else{
            final_digit = 0;
        }
        // As we are taking the digits before the decimal point, we will also remove those from the final product
        final_product = final_product.substr(final_product.size() - num.size());
        // Let us remove any trailing zeros(as this represents the fractional part)
        final_product = final_product.substr(0, final_product.find_last_not_of('0') + 1);
        return final_product;
    }
    void set_digits(vector<uint64_t> dig){
        digits = dig;
    }
    vector<uint64_t> convert_integer_to_base_2_64(string num){
            // Given just a string(guaranteed to be an integer), we will convert it to a vector of 64 bit integers
            // remainder is the remainder of the division
            vector<uint64_t> digits;
            vector<uint64_t> remainder_vec;
            while(num.length() > 0){
                uint64_t remainder = 0;
                num = long_divide_power_2(num, 32, remainder);
                if(num != "0"){
                    remainder_vec.push_back(remainder);
                }
                else{
                    // In this case push the remainder to the remainder vector
                    if (remainder > 0){
                        remainder_vec.push_back(remainder);
                    }
                    break;
                }
            }


            /* Now we have to convert the remainder vector to a vector of 64 bit integers
               How do we do this? Simple, we take use a bunch of mask and shifts 
               We look for pairs of consecutive 32 bit integers and convert them to a 64 bit integer */

            bool first_found = false;
            uint64_t prev_num = 0;
            for(auto remainder : remainder_vec){
                if(!first_found){
                    prev_num = remainder;
                    first_found = true;
                }
                else{
                    uint64_t base_64_version = (remainder << 32) | prev_num;
                    digits.push_back(base_64_version);
                    first_found = false;
                }
                
            }
            if(first_found){
                digits.push_back(prev_num);
            } 
        return digits;
    }
    vector<uint64_t> convert_decimal_to_base_2_64(string num){
        /*
        Here we will constantly multiple the number and get the remaining digit 
        We will store the digits in a vector of 64 bit integers. 
        Note we will go on to precision digits, after that we will stop(only in the case of a decimal)
        */
       vector<uint64_t> digits_32;
       int exponent = 0;
       while(num.length() > 0 && exponent < precision){
           uint64_t remainder = 0;
           num = multiply_by_power_of_2_for_decimal(num, 32, remainder);
           digits_32.push_back(remainder);
           exponent++;
       } 
       // This are actually uint32_t integers remainders of the division
       // We will convert them to 64 bit integers
         vector<uint64_t> digits;
        for(int i = 0; i < digits_32.size(); i += 2){
            uint64_t base_64_version = 0;
            if(i + 1 < digits_32.size()){
                base_64_version = (digits_32[i] << 32) | digits_32[i + 1];
            }
            else{
                base_64_version = digits_32[i] << 32;
            }
            digits.push_back(base_64_version);
        }
        return digits;
    }
    vector<uint64_t> multiply_base_2_64(vector<uint64_t>& num, uint64_t multiplier, uint64_t& final_remainder){
        /*
            This is for decimal, we will take the digits and multiply them by a 64 bit integer. 
            After which we will store the result in the digits vector. 
            We will use 128 bit integers to store the result of the multiplication. 
        */

       vector<uint64_t> result;
         __uint128_t carry = 0;
        for(int i = num.size() - 1; i >= 0; i--){
            __uint128_t product = (__uint128_t)num[i] * multiplier + carry;
            carry = product >> 64;
            result.push_back((uint64_t)product);
        }
        if(carry > 0){
            final_remainder = carry;
            result.push_back((uint64_t)carry);
        }
        else{
            final_remainder = 0;
        }
        // Same as multiplication of a decimal number with a base_2 we take out the remainder and return it
        // Take a slice of the result vector
        if(final_remainder != 0){
            result = vector<uint64_t>(result.begin(), result.end() - 1);
        }
        reverse(result.begin(), result.end());
        return result;
    }


    void convert_to_num(string num){
        /*
        We will continuously divide the integer by 2^32 and store the remainder in the digits vector.
        We will continuously long divide the integer by 2^32. We will take the resulting quotient 
        and then divide it again and again until it zero. We will take the remainder and store it in the digits vector.

        May the force be with us.
        */


            if (num == "0"){
                digits.push_back(0);
                negative = false;// Zero is not negative and not positive, but we will consider it positive(easier that way for now)
                return;
            }


            /* If there is a decimal point, we will remove it have convert the two parts separately, 
            and then add them together, to form one number. Before we do we will store the exponent(of the newly formed number)
            */
            size_t decimal_point = num.find(".");
            string decimal_val = "";
            string integer_val = num;
            if(decimal_point != string::npos){
                integer_val = num.substr(0, decimal_point);
                decimal_val = num.substr(decimal_point + 1);
                // Take out any traiing zeros from the decimal part
                decimal_val = decimal_val.substr(0, decimal_val.find_last_not_of('0') + 1);
            }

            // If there are any leading zeros, other than the first digit, we will have an error 
            string zero_lis = "";
            if(integer_val != "0" && leading_zeros(integer_val, zero_lis) ){// Change the leading zeros function 
                cerr << "Error, leading zeros in the integer part of the number" << endl;
                exit(1);
            }

            vector<uint64_t> integer_digits; // Now we have the integer part  in base 2^64
            if(integer_val[0] != '0'){// Integer part is zero no integer digits
                integer_digits = convert_integer_to_base_2_64(integer_val);
            }

            vector<uint64_t> decimal_digits = convert_decimal_to_base_2_64(decimal_val); // Now we have the decimal part in base 2^64
            // The length of our decimal part is the exponent
            exponent = decimal_digits.size();
            // Now we will combine the two vectors together to form one 
            digits = decimal_digits;
            // Now we will add the integer part to the digits vector
            for(auto digit : integer_digits){
                digits.push_back(digit);
            } // And voila we have our number, arbitrary precision number. 
        

        }
    
    string convert_integer_to_string(vector<uint64_t> digits){

        /*
        We will use an unsigned 128 bit integer to store the digits of the integer. We will divide each digit 
        by 10 and store the remainder in the digits vector. We will then take the quotient and divide it by 10 again

        As we also have an exponent, we will have to take that into account
        */
        // Printing the decimal representation of the integer

        string final_num = "";
        if(digits.size() == 1 && digits[0] == 0){
            final_num = "0";
            return final_num;
        }
        else if(digits.size() == 0){
            return "";
        }
        // We will use the long division method to print the integer
        // Looping through the digits in reverse order

        //Create a copy of the digits vector
        vector<uint64_t> digits_copy = digits;
        // Reverse the digits
        reverse(digits_copy.begin(), digits_copy.end());
        vector<uint64_t> quotient;
        uint64_t remainder = 0;
        vector<uint64_t> remainder_vec;
        int count = 0;
        while(!(digits_copy.size() == 1 && digits_copy[0] == 0)){ // While the digits vector is not only one element and that element is 0
            quotient = long_divide_integer_base2_64(digits_copy, 10, remainder);
            remainder_vec.push_back(remainder);
            digits_copy = quotient;
            count ++;
        }
        // Print the remainder vector in reverse order
        for(int i = remainder_vec.size() - 1; i >= 0; i--){
            uint64_t remainder = remainder_vec[i];
            final_num += std::to_string(remainder_vec[i]);
        }
        return final_num;
    }

    string convert_decimal_to_string(vector<uint64_t> digits, int precision = 50){
        
        string final_num = "";
        int exponent = 0;
        while( digits.size() > 0 && exponent < precision){ // Do we need the exponent here?
            // Multiply the number by 10 and store the remainder
            uint64_t remainder = 0;
            digits = multiply_base_2_64(digits, 10, remainder);
            final_num += std::to_string(remainder);
            exponent++;
        }

        return final_num;

    }
    void round_base_10(string& num){
        /*
        We will round the number to the precision specified
        */

        // So we start from one end and we check if the last number is greater than 5, if it is we will add 1 to the next number, if not cut off the rest of the numbers
        // We will start from the precision and go to the end of the number
        int index = num.size() - 1;
        int count = 0;
        if(num[index] >= '5'){
            // Then we will add 1 to the last value and then check if it is greater than 9, if so we will set it to zero and add 1 to the next value
            num[index] = num[index] + 1;
            while(num[index] > '9'){
                num[index] = '0';
                index--;
                if(index < 0){
                    // Then we will add a 1 to the beginning of the number
                    num = "1" + num;
                    break;
                }
                else{
                    num[index] = num[index] + 1;
                }
            }
        }
        else{
            // then set the last value to zero
            num[index] = '0';
        }
    }
    string to_string(int precision){
    /*
    We will convert the number to a string, by converting the integer and decimal part separately and then adding them together
    */
   // Take the sub vector of the digits vector
    string negative_str = "";
    if(negative){
        negative_str = "-";
    }
    vector<uint64_t> integer_part = vector<uint64_t>(digits.begin() + exponent, digits.end());
    string integer_part_str = convert_integer_to_string(integer_part);
    string decimal_part_str = convert_decimal_to_string(vector<uint64_t>(digits.begin(), digits.begin() + exponent), precision);
    round_base_10(decimal_part_str);
    // Take out any strailing zeros for the decimal part
    clean_trailing_zeros(decimal_part_str);
    
    if(integer_part_str == ""){
        return ( negative_str + "0." + decimal_part_str);
    } 
    else if (decimal_part_str != ""){
        return (negative_str + integer_part_str + "." + decimal_part_str);
    }
    else{
        return negative_str + integer_part_str;
    }

    }

    void clean_zeros(vector<uint64_t>& digits){
        // We will remove any leading zeros and trailing decimal zeros from the digits vector
        while(digits.size() > 1 && digits[digits.size() - 1] == 0){
            digits.pop_back();
        }
        while(digits.size() > 1 && digits[0] == 0){
            digits.erase(digits.begin());
        }
    }
    void clean_trailing_zeros(string& digits){
        // We will remove any leading zeros from the digits string
        while(digits.size() > 1 && digits[digits.size() - 1] == '0'){
            digits = digits.substr(0, digits.size() - 1);
        }
    }
    void clean_leading_zeros(string& digits){
        // We will remove any leading zeros from the digits string
        while(digits.size() > 1 && digits[0] == '0'){
            digits = digits.substr(1);
        }
    }     
    shared_ptr<Num> add_internal(shared_ptr<Num> memory){
        /* 
        We will add the two vectors of 64 bit integers
        This will be effectively a full adder lol. 
        
        4 cases we have to consider 
        positive + positive
        positive + negative
        negative + positive -> same as positive + negative
        negative + negative -> same as positive + positive

        The trickiest part is dealing with the decimal, we will have to pad the smaller number with virtual zeros 
        and then add them together, as if they were the same size.
         */
        // Cast to Int
        if(!dynamic_pointer_cast<Num>(memory)){
            cerr << "Error, trying to add a non integer to an integer" << endl;
            exit(1);
        }
        shared_ptr<Num> int_memory = dynamic_pointer_cast<Num>(memory);
        bool this_negative = negative;
        bool other_negative = int_memory->get_negative();
 
        if(!this_negative && !other_negative){
            int new_exponent = 0;
            // Both are positive
            vector<uint64_t> result = add_same_sign(digits, int_memory->get_digits(), exponent, int_memory->get_exponent(), new_exponent);
            return shared_ptr<Num>(new Num(result, false, new_exponent));
        }
        else if(this_negative && !other_negative){
            // This is negative, other is positive
            int new_exponent = 0;
            //Take whichever is greater 
            bool this_greater = is_greater_or_equal(digits, int_memory->get_digits(), exponent, int_memory->get_exponent());
            if(this_greater){
                return shared_ptr<Num>(new Num(subtract_different_sign(digits, int_memory->get_digits(), exponent, int_memory->get_exponent(), new_exponent), true, new_exponent));
            }
            else{
                return shared_ptr<Num>(new Num(subtract_different_sign(int_memory->get_digits(), digits, int_memory->get_exponent(), exponent, new_exponent), false, new_exponent));
            }
        }
        else if(!this_negative && other_negative){
            // This is positive, other is negative
            // Take whichever is greater
            int new_exponent = 0;
            bool this_greater = is_greater_or_equal(digits, int_memory->get_digits(), exponent, int_memory->get_exponent());
            if(this_greater){
                return shared_ptr<Num>(new Num(subtract_different_sign(digits, int_memory->get_digits(), exponent, int_memory->get_exponent(), new_exponent), false, new_exponent));
            }
            else{
                return shared_ptr<Num>(new Num(subtract_different_sign(int_memory->get_digits(), digits, int_memory->get_exponent(), exponent, new_exponent), true, new_exponent));
            }
        }
        else{
            // Both are negative
            int new_exponent = 0;
            vector<uint64_t> result = add_same_sign(digits, int_memory->get_digits() , exponent, int_memory->get_exponent(), new_exponent);
            return shared_ptr<Num>(new Num(result, true, new_exponent));

        }
    }
    shared_ptr<Num> sub_internal(shared_ptr<Num> other_memory){
        // Essentially the same as add except for the other memory we will negate it
        // and then call add lol(you see what I did there)
        shared_ptr<Num> int_memory = dynamic_pointer_cast<Num>(other_memory);
        int_memory->set_negative(!int_memory->get_negative());
        return add(int_memory);

    }
    shared_ptr<Num> mul_internal(shared_ptr<Num> other_memory){
        /*
        We will multiply the two numbers together, and then return the result. 
        For now this is normal multiplication grad school style, but soon it will be 
        FFT style :)
        */
       
       /* It doesn't matter which side you pick to iterate over 
        We will multiply each digit of the first number by each digit of the second number, 
        shift the product by the index of the digit and then add them together. 
        The sum can be stored in a vector of 128 bit integer which will be shifter to the right 
        by 64 bits and the remainder will be the carry over.

        I know right sooooo inefficient, but we will optimize later.  
       */

      // If one is just zero, then the result is zero
      if((digits.size() == 1 && digits[0] == 0) || (other_memory->get_digits().size() == 1 && other_memory->get_digits()[0] == 0)){
          return shared_ptr<Num>(new Num("0"));
      }

        // Currently the format is strange suppose for a second a number is 1234.45
        //(in base 2^64) the way it is stored is 45 1234, so we will have to reverse the digits
        // So the decimal part(not the integer part, we will change this just lazy :)) for both should be reversed
        vector<uint64_t> integer1 = vector<uint64_t>(digits.begin() + exponent, digits.end());
        cout<<other_memory->get_exponent()<<endl;
        vector<uint64_t> integer2 = vector<uint64_t>(other_memory->get_digits().begin() + other_memory->get_exponent(), other_memory->get_digits().end());
        vector<uint64_t> decimal1 = vector<uint64_t>(digits.begin(), digits.begin() + exponent);
        vector<uint64_t> decimal2 = vector<uint64_t>(other_memory->get_digits().begin(), other_memory->get_digits().begin() + other_memory->get_exponent());  

        reverse(decimal1.begin(), decimal1.end());
        reverse(decimal2.begin(), decimal2.end());

        // Now combine the two vectors together(just insert the integers in there respective places)
        // totally unnecessary, but I am lazy, I really should just reverse the digits at the beggining
        // but why do that when you can do it later right? Stop judging me, focus on the code

        for( auto integer : integer1){
            decimal1.push_back(integer);
        }
        for(auto integer : integer2){
            decimal2.push_back(integer);
        }

        // Now we will multiply the two numbers together
        vector< vector<uint64_t> > intermediate_products;

        for(int i = 0; i < decimal1.size(); i++){
            vector<uint64_t> intermediate_product;
            __uint128_t carry = 0;
            // Add zeros aat the beginning of the intermediate product, simulating a shift
            for(int j = 0; j < i; j++){
                intermediate_product.push_back(0);
            }
            for(int j = 0; j < decimal2.size(); j++){
                __uint128_t product = (__uint128_t)decimal1[i] * (__uint128_t)decimal2[j] + carry;
                product = product >> 64;
                if(product > 0){
                    // The carry is 2^64, so we will take the remainder and add it to the next product
                    carry =  1 << 64;
                }
                intermediate_product.push_back((uint64_t)product);
            }
            if(carry > 0){ // If there is a carry then we will add a zero and a 11
                intermediate_product.push_back(0);
                intermediate_product.push_back(1);
            }
            intermediate_products.push_back(intermediate_product);
        }

        // Pad the intermediate products with zeros
        int max_size = 0;
        // Loop through and get the maximum size
        for(auto product : intermediate_products){
            if(product.size() > max_size){
                max_size = product.size();
            }
        }
        // Add zeros to the end of the products
        for(int i = 0; i < intermediate_products.size(); i++){
            for(int j = intermediate_products[i].size(); j < max_size; j++){
                intermediate_products[i].push_back(0);
            }
        }

        // Now we will add the intermediate products together
        vector<uint64_t> result;
        __uint128_t carry = 0;
        for(int i = 0; i < max_size; i++){
            __uint128_t sum = 0;
            for(auto product : intermediate_products){
                sum += (__uint128_t)product[i];
            }
            sum += carry;
            carry = sum >> 64;
            result.push_back((uint64_t)sum);
        }
 

        // Only trick here is we need to reverse the decimal part, then recombine 
        // I know, I know I should have just reversed the digits at the beginning, but I was lazy
        int new_exponent = exponent * other_memory->get_exponent();
        vector<uint64_t> integer_result = vector<uint64_t>(result.begin() + new_exponent, result.end());
        vector<uint64_t> decimal_result = vector<uint64_t>(result.begin(), result.begin() + new_exponent);
        reverse(decimal_result.begin(), decimal_result.end());

        int min_precision = min(precision, other_memory->get_precision());

        // We take the minimum of the precision and the exponent
        while(decimal_result.size() > min_precision){
            decimal_result.pop_back();
        }

        for(auto integer : integer_result){
            decimal_result.push_back(integer);
        }
        new_exponent = decimal_result.size();

        bool neg = negative ^ other_memory->get_negative();
        return shared_ptr<Num>(new Num(decimal_result, neg, new_exponent));

    }
    void set_negative(bool neg){
        negative = neg;
    }


    bool is_greater_or_equal(vector<uint64_t> left, vector<uint64_t> right, int exponent_left, int exponent_right){
        /*
        We want to pad the digits with the lower exponent with zeros, so that we can compare them. 
        As this is inefficient, we will act(fake it till you make it) like it is padded, and then compare the two numbers.
        */

       // First check to see if the integer part is greater if not go to the exponent 

       if(left.size() - exponent_left > right.size() - exponent_right){
           return true;
       }
       else if(left.size() - exponent_left < right.size() - exponent_right){
           return false;
       }
     
     // Now loop through the integer digits(they are the same size right), and then see which is greater
    // Start from the end of vector as the most significant digit is at the end
    for(int i = left.size() - 1; i >= exponent_left; i--){
        if(left[i] > right[i]){
            return true;
        }
        else if(left[i] < right[i]){
            return false;
        }
    }
    // Now we will compare the decimal parts
    // The decimal parts are in reverse right so the most significant digit is at the beginning
    // Also we are comparing the digits up to the minimum exponent of the two numbers
    int min_exponent = min(exponent_left, exponent_right);
    for(int i = 0; i < min_exponent; i++){
        if(left[i] > right[i]){
            return true;
        }
        else if(left[i] < right[i]){
            return false;
        }
    }
        // If the decimal parts are the same, then the number with the greater exponent is greater
        if(exponent_left > exponent_right){
            return true;
        }
        // The numbers are equal
        return true;
    }

    vector<uint64_t> add_same_sign(vector<uint64_t> digits1, vector<uint64_t> digits2, int exponent1, int exponent2, int& new_exponent){
        /* 
            Same sign addition
            We have two nums, with exponents that we want to add together. 
            For simplicity we will pad the smaller number with zeros, so that they are the same size.
            We will first add the decimal parts, and then the integer parts. 
            We take the carry over from the decimal part and add it to the integer part. 
        */
        vector<uint64_t> result;
        __uint128_t carry = 0;
        int max_exponent = max(exponent1, exponent2);

        // Extract the decimal parts 
        vector<uint64_t> decimal1 = vector<uint64_t>(digits1.begin(), digits1.begin() + exponent1);
        vector<uint64_t> decimal2 = vector<uint64_t>(digits2.begin(), digits2.begin() + exponent2);
        int min_size = min( exponent1, exponent2);
        // Add the remaining digits specifically, remaining digits are lesser significant ones 
        if(decimal1.size() > decimal2.size()){
            // If it is then directly add the remaining digits, without any carry
            // Again we will go from the end of decimal1 to the min index
            for(int i = decimal1.size() - 1; i >= min_size ; i--){
                result.push_back(decimal1[i]);
            }
        }
        else if( decimal2.size() > decimal1.size()){
            for(int i = decimal2.size() - 1; i >= min_size ; i--){
                result.push_back(decimal2[i]);
            }
        } 
        // Now add but in reverse
        for (int i = min_size - 1; i >= 0; i--){
            __uint128_t sum = (__uint128_t)decimal1[i] + (__uint128_t)decimal2[i] + carry;
            carry = sum >> 64;
            result.push_back(sum);
        }
        // Clear any trailing zeros
        while(result.size() > 1 && result.back() == 0 ){
            result.pop_back();
        }
        reverse(result.begin(), result.end());

        // Now we will add the integer parts
        vector<uint64_t> integer1 = vector<uint64_t>(digits1.begin() + exponent1, digits1.end());
        vector<uint64_t> integer2 = vector<uint64_t>(digits2.begin() + exponent2, digits2.end());

        // Add padding 
        while(integer1.size() < integer2.size()){
            integer1.push_back(0);
        }
        while(integer2.size() < integer1.size()){
            integer2.push_back(0);
        }
        for(int i = 0 ; i < integer1.size(); i++){ // Most significant digit is last in the vector
            __uint128_t sum = (__uint128_t)integer1[i] + (__uint128_t)integer2[i] + carry;
            carry = sum >> 64;
            result.push_back(sum);
        }
        // Add the carry to the result
        if(carry > 0){
            result.push_back(carry);
        }
        new_exponent = max_exponent;
        return result;
    }
    vector<uint64_t> subtract_different_sign(vector<uint64_t> left, vector<uint64_t> right, int exponent1, int exponent2, int& new_exponent){
        /*
            Different sign addition 
            We know the left is greater than the right

            Subtraction is similar to addition, the only difference being, 
            we borrow from right to left, the act of borrowing is  
            subtracting 1 from the digit to the left and adding 2^64 to the digit

            So first take figure out which digit is greater, if the positives digit is greater than the negatives digit
            then we can subtract the two digits, and we will not have to borrow.

            If the negative is greater than the positive, then we will have to borrow, but as 
            we are dealing with unsigned integers, we dont have to change the subtracted output 
            by default we have a - b + 2^64 = a - b in unisigend arithmetic!
            That is the basic idea, let's go!
            */

        // Do the decimal first 
        vector<uint64_t> result;
        char borrow = 0; 
        // Extract the decimal parts
        vector<uint64_t> decimal1 = vector<uint64_t>(left.begin(), left.begin() + exponent1);
        vector<uint64_t> decimal2 = vector<uint64_t>(right.begin(), right.begin() + exponent2);

        int min_exponent = min(exponent1, exponent2);
        // Aa subtraction requires the digits to be the same size, and we can't just drop the 
        // digits of the lower exponent decimal part(we might have a case where decimal2 is greater than decimal1 at that digit)
        // We will just pad, for now of optimization we will pad the smaller one with zeros
        while(decimal1.size() < decimal2.size()){
            decimal1.push_back(0);
        }
        while(decimal2.size() < decimal1.size()){
            decimal2.push_back(0);
        }

        // Subtract the decimals(only difference is we are doing it in reverse)
        for(int i = decimal1.size() - 1; i >= 0; i--){
            uint64_t diff = decimal1[i] - decimal2[i] - borrow;
            if(diff > decimal1[i]){
                borrow = 1;
            }
            else{
                borrow = 0;
            }
            result.push_back(diff);
        }

        while(result.size() > 1 && result.back() == 0){
            result.pop_back();
        }
        // Reverse the result
        reverse(result.begin(), result.end());

        vector<uint64_t> integer1 = vector<uint64_t>(left.begin() + exponent1, left.end());
        vector<uint64_t> integer2 = vector<uint64_t>(right.begin() + exponent2, right.end());

        while(integer1.size() < integer2.size()){
            integer1.push_back(0);
        }
        while(integer2.size() < integer1.size()){
            integer2.push_back(0);
        }

        // Subtract the integers
        for(int i = 0; i < integer1.size(); i++){
            uint64_t diff = integer1[i] - integer2[i] - borrow;
            if(diff > integer1[i]){
                borrow = 1;
            }
            else{
                borrow = 0;
            }
            result.push_back(diff);
        }

        new_exponent = max(exponent1, exponent2);
        return result;
    }


    vector<uint64_t>& get_digits(){
        return digits;
    }
    bool get_negative(){
        return negative;
    }
    // Now define all the operations
    shared_ptr<Num> add(shared_ptr<Num> int_memory){
        return add_internal(int_memory);
    }
    shared_ptr<Num> sub (shared_ptr<Num> int_memory){
        // Subtract the two numbers
        return sub_internal(int_memory);
    }
    shared_ptr<Num> mul (shared_ptr<Num> int_memory){
        // Multiply the two numbers
        return mul_internal(int_memory);
    }
    // shared_ptr<Num> div (shared_ptr<Num> int_memory){
    //     // Divide the two numbers
    //     return div_internal(int_memory);
    // }
    // shared_ptr<Num> mod (shared_ptr<Num> int_memory){
    //     // Modulus of the two numbers
    //     return mod_internal(int_memory);
    // }
    // Return bools for comparison operations
    // is_greater_or_equal is the main function 
    shared_ptr<Bool> equal(shared_ptr<Num> int_memory){
        // Check if the two have the same sign and the same digits up to the smallest exponent
        if(negative != int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(false));
        }
        if(digits.size() != int_memory->get_digits().size()){
            return shared_ptr<Bool>(new Bool(false));
        }
        int min_exponent = min(exponent, int_memory->get_exponent());
        for(int i = 0; i < min_exponent; i++){
            if(digits[i] != int_memory->get_digits()[i]){
                return shared_ptr<Bool>(new Bool(false));
            }
        }
        // Now check the integer part, start from the opposite end and go to finish of the integer part
        if(digits.size() - exponent != int_memory->get_digits().size() - int_memory->get_exponent()){
            return shared_ptr<Bool>(new Bool(false));
        }
        for(int i = digits.size() - 1; i >= exponent; i--){
            if(digits[i] != int_memory->get_digits()[i]){
                return shared_ptr<Bool>(new Bool(false));
            }
        }
        return shared_ptr<Bool>(new Bool(digits == int_memory->get_digits()));
    }
    shared_ptr<Bool> not_equal(shared_ptr<Num> int_memory){
        // Use the equal function and then negate the result
        return shared_ptr<Bool>(new Bool(!equal(int_memory)->get_val()));
    }
    shared_ptr<Bool> less(shared_ptr<Num> int_memory){
        // dont forget to get the negative sign
        if(negative && !int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(true));
        }
        else if(!negative && int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(false));
        }
        return shared_ptr<Bool>(new Bool(!is_greater_or_equal(digits, int_memory->get_digits(), exponent, int_memory->get_exponent())));
    }
    shared_ptr<Bool> greater(shared_ptr<Num> int_memory){
        if(negative && !int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(false));
        }
        else if(!negative && int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(true));
        }
        return shared_ptr<Bool>(new Bool(is_greater_or_equal(digits, int_memory->get_digits(), exponent, int_memory->get_exponent())));
    }
    shared_ptr<Bool> less_equal(shared_ptr<Num> int_memory){
        if(negative && !int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(true));
        }
        else if(!negative && int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(false));
        }
        return shared_ptr<Bool>(new Bool(is_greater_or_equal(int_memory->get_digits(), digits, int_memory->get_exponent(), exponent)));
    }
    shared_ptr<Bool> greater_equal(shared_ptr<Num> int_memory){
        if(negative && !int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(false));
        }
        else if(!negative && int_memory->get_negative()){
            return shared_ptr<Bool>(new Bool(true));
        }
        return shared_ptr<Bool>(new Bool(is_greater_or_equal(digits, int_memory->get_digits(), exponent, int_memory->get_exponent())));
    }


};
