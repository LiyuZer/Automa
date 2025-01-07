#include <iostream>
#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#include "../typesdef/bool.h"

/*
This is the file for defining integer types(soon to be num type, one numbers class to control them all), because I am crazy I will make them arbitrary precision. 
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
    type : "int"
}

For ints all operations will be implemented as part of the class, rather than a symbol pointing to a graph.
The reason being speed and efficiency, these are the most common operations and we want them to be as fast as possible.

We will implement addition, subtraction, multiplication, division, modulo, equal, not equal, less, greater, less equal, greater equal, and, or, not.

We will store in memory the digits of the integer, and the sign of the integer.
Let the games begin. 
*/

class Int : public Memory{
    private:
    vector<uint64_t> digits;
    bool negative;
    public:
    Int(string integer) : Memory("int"){
        if (integer[0] == '-'){
            negative = true;
            integer = integer.substr(1);
        }
        else{
            negative = false;
        }
        convert_to_int(integer);

        // Set Memory container
        set_immutable(true);

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
    // This function will remove leading zeros from the integer, and update 
    // zero list with zeros that were removed
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
    /* This function will divide the dividend by the divisor and return the remainder
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
            final_quotient += to_string(quotient);
        }
        else{
            final_quotient += "0"; // Regardless of the remainder we add a zero
        }

        if(remainder > 0){
            current_dividend = to_string(remainder);
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
    Int(vector<uint64_t> dig, bool neg) : Memory(){
        digits = dig;
        negative = neg;
        set_immutable(true);
    }
    void set_digits(vector<uint64_t> dig){
        digits = dig;
    }
    void convert_to_int(string integer){
        /*
        We will continuously divide the integer by 2^32 and store the remainder in the digits vector.
        We will also take only 19 digits at a time as 10^19 is the largest power of 10 that can be stored in a 64 bit integer. 
        We will continuously long divide the integer by 2^32. We will take the resulting quotient 
        and then divide it again and again until it zero. We will take the remainder and store it in the digits vector.
        May the force be with us.
        */

            if (integer == "0"){
                digits.push_back(0);
                negative = false;// Zero is not negative and not positive, but we will consider it positive(easier that way for now)
                return;
            }
            // remainder is the remainder of the division
            vector<uint64_t> remainder_vec;
            while(integer.length() > 0){
                uint64_t remainder = 0;
                integer = long_divide_power_2(integer, 32, remainder);
                if(integer != "0"){
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

        }
    void print(){

        /*
        We will use an unsigned 128 bit integer to store the digits of the integer. We will divide each digit 
        by 10 and store the remainder in the digits vector. We will then take the quotient and divide it by 10 again
        */
        // Printing the decimal representation of the integer

        if(digits.size() == 1 && digits[0] == 0){
            cout << "0";
            return;
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
        if(negative){
            cout << "-";
        }
        // Print the remainder vector in reverse order
        for(int i = remainder_vec.size() - 1; i >= 0; i--){
            cout << remainder_vec[i];
        }
    }

    shared_ptr<Int> add_internal(shared_ptr<Int> memory){
        /* 
        We will add the two vectors of 64 bit integers
        This will be effectively a full adder lol. 
        
        4 cases we have to consider 
        positive + positive
        positive + negative
        negative + positive -> same as positive + negative
        negative + negative -> same as positive + positive
         */
        // Cast to Int
        if(!dynamic_pointer_cast<Int>(memory)){
            cerr << "Error, trying to add a non integer to an integer" << endl;
            exit(1);
        }
        shared_ptr<Int> int_memory = dynamic_pointer_cast<Int>(memory);
        bool this_negative = negative;
        bool other_negative = int_memory->get_negative();

        if(!this_negative && !other_negative){
            // Both are positive
            vector<uint64_t> result = add_same_sign(digits, int_memory->get_digits());
            return shared_ptr<Int>(new Int(result, false));
        }
        else if(this_negative && !other_negative){
            // This is negative, other is positive

            //Take whichever is greater 
            bool this_greater = is_greater_or_equal(digits, int_memory->get_digits());
            if(this_greater){
                return shared_ptr<Int>(new Int(subtract_different_sign(digits, int_memory->get_digits()), true));
            }
            else{
                return shared_ptr<Int>(new Int(subtract_different_sign(int_memory->get_digits(), digits), false));
            }
        }
        else if(!this_negative && other_negative){
            // This is positive, other is negative
            // Take whichever is greater
            bool this_greater = is_greater_or_equal(digits, int_memory->get_digits());
            if(this_greater){
                return shared_ptr<Int>(new Int(subtract_different_sign(digits, int_memory->get_digits()), false));
            }
            else{
                return shared_ptr<Int>(new Int(subtract_different_sign(int_memory->get_digits(), digits), true));
            }
        }
        else{
            // Both are negative
            vector<uint64_t> result = add_same_sign(digits, int_memory->get_digits());
            return shared_ptr<Int>(new Int(result, true));

        }
    }
    shared_ptr<Int> sub_internal(shared_ptr<Int> other_memory){
        // Essentially the same as add except for the other memory we will negate it
        // and then call add lol(you see what I did there)
        shared_ptr<Int> int_memory = dynamic_pointer_cast<Int>(other_memory);
        int_memory->set_negative(!int_memory->get_negative());
        return add(int_memory);

    }
    void set_negative(bool neg){
        negative = neg;
    }


    bool is_greater_or_equal(vector<uint64_t> left, vector<uint64_t> right){
        // Check if left is greater than or equal to right
        if(left.size() > right.size()){
            return true;
        }
        else if(left.size() < right.size()){
            return false;
        }
        else{
            for(int i = left.size() - 1; i >= 0; i--){
                if(left[i] > right[i]){
                    return true;
                }
                else if(left[i] < right[i]){
                    return false;
                }
            }
            return true;
        }
    }

    vector<uint64_t> add_same_sign(vector<uint64_t> digits1, vector<uint64_t> digits2){
        // Same sign addition
        vector<uint64_t> result;
        uint64_t carry = 0;
        int max_size = max(digits1.size(), digits2.size());
        // Pad which ever is smaller with zeros, lazy approach
        while(digits1.size() < max_size){
            digits1.push_back(0);
        }
        while(digits2.size() < max_size){
            digits2.push_back(0);
        }
        for(int i = 0; i < max_size; i++){
            uint64_t sum = 0;
            sum = digits1[i] + digits2[i] + carry;
            if(sum >= digits1[i] && sum >= digits2[i]){
                carry = 0;
            }
            else{
                carry = 1;
            }
            result.push_back(sum);
        }
        // If there is a carry at the end
        if(carry == 1){
            result.push_back(1);
        }
        return result;
    }
    vector<uint64_t> subtract_different_sign(vector<uint64_t> left, vector<uint64_t> right){
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
        vector<uint64_t> result;
        char borrow = 0; 
        while(right.size() < left.size()){
            right.push_back(0);
        }
        while (left.size() < right.size()){
            left.push_back(0);
        }
        for(int i = 0; i < left.size(); i++){
            uint64_t diff = left[i] - right[i] - borrow;
            // If diff is greater than left[i], then we have to borrow
            // As then right[i] is greater than left[i]
            if(diff > left[i]){
                borrow = 1;
            }
            else{
                borrow = 0;
            }
             result.push_back(diff);
        }
        // Borrow bit must be 0 at the end
        // Take out trailing zeros 
        while(result.back() == 0 && result.size() > 1){
            result.pop_back();
        }
        return result;
    }


    vector<uint64_t> get_digits(){
        return digits;
    }
    bool get_negative(){
        return negative;
    }
    // Now define all the operations
    shared_ptr<Int> add(shared_ptr<Int> int_memory){
        return add_internal(int_memory);
    }
    shared_ptr<Int> sub (shared_ptr<Int> int_memory){
        return sub_internal(int_memory);
    }
    // Return bools for comparison operations
    // is_greater_or_equal is the main function 
    shared_ptr<Bool> equal(shared_ptr<Int> int_memory){
        return shared_ptr<Bool>(new Bool(digits == int_memory->get_digits()));
    }
    shared_ptr<Bool> not_equal(shared_ptr<Int> int_memory){
        return shared_ptr<Bool>(new Bool(digits != int_memory->get_digits()));
    }
    shared_ptr<Bool> less(shared_ptr<Int> int_memory){
        return shared_ptr<Bool>(new Bool(!is_greater_or_equal(digits, int_memory->get_digits())));
    }
    shared_ptr<Bool> greater(shared_ptr<Int> int_memory){
        return shared_ptr<Bool>(new Bool(is_greater_or_equal(digits, int_memory->get_digits())));
    }
    shared_ptr<Bool> less_equal(shared_ptr<Int> int_memory){
        return shared_ptr<Bool>(new Bool(is_greater_or_equal(int_memory->get_digits(), digits)));
    }
    shared_ptr<Bool> greater_equal(shared_ptr<Int> int_memory){
        return shared_ptr<Bool>(new Bool(is_greater_or_equal(digits, int_memory->get_digits())));
    }


};
