// Generated from /Users/liyuzerihun/Automa/grammar/AUTOMAParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class AUTOMAParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		Operator=1, Transitions=2, Graph=3, Memory=4, AfterReject=5, AfterAccept=6, 
		Symbols=7, Array=8, Dict=9, Tuple=10, Conditions=11, Operations=12, None=13, 
		NodeDef=14, StartNode=15, AcceptNode=16, RejectNode=17, Arrow=18, ArrowEquals=19, 
		LeftParen=20, RightParen=21, LeftBracket=22, RightBracket=23, LeftBrace=24, 
		RightBrace=25, Plus=26, Minus=27, Star=28, Div=29, Mod=30, And=31, Or=32, 
		Tilde=33, Not=34, Assign=35, Less=36, Greater=37, Equal=38, NotEqual=39, 
		LessEqual=40, GreaterEqual=41, Semicolon=42, DoubleColon=43, Colon=44, 
		Comma=45, BooleanLiteral=46, StringLiteral=47, CharLiteral=48, IntegerLiteral=49, 
		Digit=50, IDENTIFIER=51, Whitespace=52, Newline=53, BlockComment=54, LineComment=55;
	public static final int
		RULE_r = 0, RULE_graphDef = 1, RULE_graphBody = 2, RULE_memoryDefinition = 3, 
		RULE_nodeDefinition = 4, RULE_transitionDefinition = 5, RULE_transition = 6, 
		RULE_firstNode = 7, RULE_secondNode = 8, RULE_expression = 9, RULE_booleanExpression = 10, 
		RULE_arithmeticExpression = 11, RULE_term = 12, RULE_factor = 13, RULE_expressionAtom = 14, 
		RULE_dataTypes = 15, RULE_memoryType = 16, RULE_tupleType = 17, RULE_listType = 18, 
		RULE_nodeDefTypes = 19, RULE_graphCall = 20, RULE_afterAcceptDefinition = 21, 
		RULE_afterRejectDefinition = 22, RULE_arithmeticOperator = 23, RULE_boolOperator = 24, 
		RULE_literals = 25, RULE_var = 26, RULE_booleanLiteral = 27, RULE_stringLiteral = 28, 
		RULE_charLiteral = 29, RULE_integerLiteral = 30, RULE_digit = 31;
	private static String[] makeRuleNames() {
		return new String[] {
			"r", "graphDef", "graphBody", "memoryDefinition", "nodeDefinition", "transitionDefinition", 
			"transition", "firstNode", "secondNode", "expression", "booleanExpression", 
			"arithmeticExpression", "term", "factor", "expressionAtom", "dataTypes", 
			"memoryType", "tupleType", "listType", "nodeDefTypes", "graphCall", "afterAcceptDefinition", 
			"afterRejectDefinition", "arithmeticOperator", "boolOperator", "literals", 
			"var", "booleanLiteral", "stringLiteral", "charLiteral", "integerLiteral", 
			"digit"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'operator'", "'transitions'", "'graph'", "'memory'", "'afterReject'", 
			"'afterAccept'", "'symbols'", "'array'", "'dict'", "'tuple'", "'conditions'", 
			"'operations'", "'None'", "'nodeDef'", "'startNode'", "'acceptNode'", 
			"'rejectNode'", "'->'", "'=>'", "'('", "')'", "'['", "']'", "'{'", "'}'", 
			"'+'", "'-'", "'*'", "'/'", "'%'", null, null, "'~'", null, "'='", "'<'", 
			"'>'", "'=='", "'!='", "'<='", "'>='", "';'", "'::'", "':'", "','"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "Operator", "Transitions", "Graph", "Memory", "AfterReject", "AfterAccept", 
			"Symbols", "Array", "Dict", "Tuple", "Conditions", "Operations", "None", 
			"NodeDef", "StartNode", "AcceptNode", "RejectNode", "Arrow", "ArrowEquals", 
			"LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
			"RightBrace", "Plus", "Minus", "Star", "Div", "Mod", "And", "Or", "Tilde", 
			"Not", "Assign", "Less", "Greater", "Equal", "NotEqual", "LessEqual", 
			"GreaterEqual", "Semicolon", "DoubleColon", "Colon", "Comma", "BooleanLiteral", 
			"StringLiteral", "CharLiteral", "IntegerLiteral", "Digit", "IDENTIFIER", 
			"Whitespace", "Newline", "BlockComment", "LineComment"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "AUTOMAParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public AUTOMAParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RContext extends ParserRuleContext {
		public List<GraphDefContext> graphDef() {
			return getRuleContexts(GraphDefContext.class);
		}
		public GraphDefContext graphDef(int i) {
			return getRuleContext(GraphDefContext.class,i);
		}
		public RContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_r; }
	}

	public final RContext r() throws RecognitionException {
		RContext _localctx = new RContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_r);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(67);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Graph) {
				{
				{
				setState(64);
				graphDef();
				}
				}
				setState(69);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class GraphDefContext extends ParserRuleContext {
		public TerminalNode Graph() { return getToken(AUTOMAParser.Graph, 0); }
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public GraphBodyContext graphBody() {
			return getRuleContext(GraphBodyContext.class,0);
		}
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public GraphDefContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_graphDef; }
	}

	public final GraphDefContext graphDef() throws RecognitionException {
		GraphDefContext _localctx = new GraphDefContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_graphDef);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(70);
			match(Graph);
			setState(71);
			match(IDENTIFIER);
			setState(72);
			match(LeftBrace);
			setState(73);
			graphBody();
			setState(74);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class GraphBodyContext extends ParserRuleContext {
		public MemoryDefinitionContext memoryDefinition() {
			return getRuleContext(MemoryDefinitionContext.class,0);
		}
		public NodeDefinitionContext nodeDefinition() {
			return getRuleContext(NodeDefinitionContext.class,0);
		}
		public TransitionDefinitionContext transitionDefinition() {
			return getRuleContext(TransitionDefinitionContext.class,0);
		}
		public List<AfterAcceptDefinitionContext> afterAcceptDefinition() {
			return getRuleContexts(AfterAcceptDefinitionContext.class);
		}
		public AfterAcceptDefinitionContext afterAcceptDefinition(int i) {
			return getRuleContext(AfterAcceptDefinitionContext.class,i);
		}
		public List<AfterRejectDefinitionContext> afterRejectDefinition() {
			return getRuleContexts(AfterRejectDefinitionContext.class);
		}
		public AfterRejectDefinitionContext afterRejectDefinition(int i) {
			return getRuleContext(AfterRejectDefinitionContext.class,i);
		}
		public GraphBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_graphBody; }
	}

	public final GraphBodyContext graphBody() throws RecognitionException {
		GraphBodyContext _localctx = new GraphBodyContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_graphBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(76);
			memoryDefinition();
			setState(77);
			nodeDefinition();
			setState(78);
			transitionDefinition();
			setState(82);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==AfterAccept) {
				{
				{
				setState(79);
				afterAcceptDefinition();
				}
				}
				setState(84);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(88);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==AfterReject) {
				{
				{
				setState(85);
				afterRejectDefinition();
				}
				}
				setState(90);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MemoryDefinitionContext extends ParserRuleContext {
		public TerminalNode Memory() { return getToken(AUTOMAParser.Memory, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public List<TerminalNode> IDENTIFIER() { return getTokens(AUTOMAParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(AUTOMAParser.IDENTIFIER, i);
		}
		public List<TerminalNode> Colon() { return getTokens(AUTOMAParser.Colon); }
		public TerminalNode Colon(int i) {
			return getToken(AUTOMAParser.Colon, i);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(AUTOMAParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(AUTOMAParser.Comma, i);
		}
		public MemoryDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_memoryDefinition; }
	}

	public final MemoryDefinitionContext memoryDefinition() throws RecognitionException {
		MemoryDefinitionContext _localctx = new MemoryDefinitionContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_memoryDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(91);
			match(Memory);
			setState(92);
			match(LeftBrace);
			setState(105);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(93);
				match(IDENTIFIER);
				setState(94);
				match(Colon);
				setState(95);
				expression();
				setState(102);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==Comma) {
					{
					{
					setState(96);
					match(Comma);
					setState(97);
					match(IDENTIFIER);
					setState(98);
					match(Colon);
					setState(99);
					expression();
					}
					}
					setState(104);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(107);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class NodeDefinitionContext extends ParserRuleContext {
		public TerminalNode NodeDef() { return getToken(AUTOMAParser.NodeDef, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public List<TerminalNode> IDENTIFIER() { return getTokens(AUTOMAParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(AUTOMAParser.IDENTIFIER, i);
		}
		public List<TerminalNode> DoubleColon() { return getTokens(AUTOMAParser.DoubleColon); }
		public TerminalNode DoubleColon(int i) {
			return getToken(AUTOMAParser.DoubleColon, i);
		}
		public List<NodeDefTypesContext> nodeDefTypes() {
			return getRuleContexts(NodeDefTypesContext.class);
		}
		public NodeDefTypesContext nodeDefTypes(int i) {
			return getRuleContext(NodeDefTypesContext.class,i);
		}
		public List<TerminalNode> Semicolon() { return getTokens(AUTOMAParser.Semicolon); }
		public TerminalNode Semicolon(int i) {
			return getToken(AUTOMAParser.Semicolon, i);
		}
		public NodeDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nodeDefinition; }
	}

	public final NodeDefinitionContext nodeDefinition() throws RecognitionException {
		NodeDefinitionContext _localctx = new NodeDefinitionContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_nodeDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(109);
			match(NodeDef);
			setState(110);
			match(LeftBrace);
			setState(125);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(111);
				match(IDENTIFIER);
				setState(112);
				match(DoubleColon);
				setState(113);
				nodeDefTypes();
				setState(114);
				match(Semicolon);
				setState(122);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==IDENTIFIER) {
					{
					{
					setState(115);
					match(IDENTIFIER);
					setState(116);
					match(DoubleColon);
					setState(117);
					nodeDefTypes();
					setState(118);
					match(Semicolon);
					}
					}
					setState(124);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(127);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TransitionDefinitionContext extends ParserRuleContext {
		public TerminalNode Transitions() { return getToken(AUTOMAParser.Transitions, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public List<TransitionContext> transition() {
			return getRuleContexts(TransitionContext.class);
		}
		public TransitionContext transition(int i) {
			return getRuleContext(TransitionContext.class,i);
		}
		public TransitionDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_transitionDefinition; }
	}

	public final TransitionDefinitionContext transitionDefinition() throws RecognitionException {
		TransitionDefinitionContext _localctx = new TransitionDefinitionContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_transitionDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(129);
			match(Transitions);
			setState(130);
			match(LeftBrace);
			setState(132); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(131);
				transition();
				}
				}
				setState(134); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==IDENTIFIER );
			setState(136);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TransitionContext extends ParserRuleContext {
		public FirstNodeContext firstNode() {
			return getRuleContext(FirstNodeContext.class,0);
		}
		public SecondNodeContext secondNode() {
			return getRuleContext(SecondNodeContext.class,0);
		}
		public TerminalNode ArrowEquals() { return getToken(AUTOMAParser.ArrowEquals, 0); }
		public TerminalNode Conditions() { return getToken(AUTOMAParser.Conditions, 0); }
		public List<TerminalNode> Colon() { return getTokens(AUTOMAParser.Colon); }
		public TerminalNode Colon(int i) {
			return getToken(AUTOMAParser.Colon, i);
		}
		public List<TupleTypeContext> tupleType() {
			return getRuleContexts(TupleTypeContext.class);
		}
		public TupleTypeContext tupleType(int i) {
			return getRuleContext(TupleTypeContext.class,i);
		}
		public TerminalNode Comma() { return getToken(AUTOMAParser.Comma, 0); }
		public TerminalNode Operations() { return getToken(AUTOMAParser.Operations, 0); }
		public TerminalNode Semicolon() { return getToken(AUTOMAParser.Semicolon, 0); }
		public TransitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_transition; }
	}

	public final TransitionContext transition() throws RecognitionException {
		TransitionContext _localctx = new TransitionContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_transition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(138);
			firstNode();
			setState(139);
			secondNode();
			setState(140);
			match(ArrowEquals);
			setState(141);
			match(Conditions);
			setState(142);
			match(Colon);
			setState(143);
			tupleType();
			setState(144);
			match(Comma);
			setState(145);
			match(Operations);
			setState(146);
			match(Colon);
			setState(147);
			tupleType();
			setState(148);
			match(Semicolon);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FirstNodeContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public FirstNodeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_firstNode; }
	}

	public final FirstNodeContext firstNode() throws RecognitionException {
		FirstNodeContext _localctx = new FirstNodeContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_firstNode);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(150);
			match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SecondNodeContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public SecondNodeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_secondNode; }
	}

	public final SecondNodeContext secondNode() throws RecognitionException {
		SecondNodeContext _localctx = new SecondNodeContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_secondNode);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(152);
			match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionContext extends ParserRuleContext {
		public BooleanExpressionContext booleanExpression() {
			return getRuleContext(BooleanExpressionContext.class,0);
		}
		public List<TerminalNode> Not() { return getTokens(AUTOMAParser.Not); }
		public TerminalNode Not(int i) {
			return getToken(AUTOMAParser.Not, i);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_expression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(157);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Not) {
				{
				{
				setState(154);
				match(Not);
				}
				}
				setState(159);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(160);
			booleanExpression();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BooleanExpressionContext extends ParserRuleContext {
		public List<ArithmeticExpressionContext> arithmeticExpression() {
			return getRuleContexts(ArithmeticExpressionContext.class);
		}
		public ArithmeticExpressionContext arithmeticExpression(int i) {
			return getRuleContext(ArithmeticExpressionContext.class,i);
		}
		public List<BoolOperatorContext> boolOperator() {
			return getRuleContexts(BoolOperatorContext.class);
		}
		public BoolOperatorContext boolOperator(int i) {
			return getRuleContext(BoolOperatorContext.class,i);
		}
		public BooleanExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_booleanExpression; }
	}

	public final BooleanExpressionContext booleanExpression() throws RecognitionException {
		BooleanExpressionContext _localctx = new BooleanExpressionContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_booleanExpression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(162);
			arithmeticExpression();
			setState(168);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 281320357888L) != 0)) {
				{
				{
				setState(163);
				boolOperator();
				setState(164);
				arithmeticExpression();
				}
				}
				setState(170);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArithmeticExpressionContext extends ParserRuleContext {
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public List<TerminalNode> Plus() { return getTokens(AUTOMAParser.Plus); }
		public TerminalNode Plus(int i) {
			return getToken(AUTOMAParser.Plus, i);
		}
		public List<TerminalNode> Minus() { return getTokens(AUTOMAParser.Minus); }
		public TerminalNode Minus(int i) {
			return getToken(AUTOMAParser.Minus, i);
		}
		public ArithmeticExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arithmeticExpression; }
	}

	public final ArithmeticExpressionContext arithmeticExpression() throws RecognitionException {
		ArithmeticExpressionContext _localctx = new ArithmeticExpressionContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_arithmeticExpression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(171);
			term();
			setState(176);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Plus || _la==Minus) {
				{
				{
				setState(172);
				_la = _input.LA(1);
				if ( !(_la==Plus || _la==Minus) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(173);
				term();
				}
				}
				setState(178);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TermContext extends ParserRuleContext {
		public List<FactorContext> factor() {
			return getRuleContexts(FactorContext.class);
		}
		public FactorContext factor(int i) {
			return getRuleContext(FactorContext.class,i);
		}
		public List<TerminalNode> Star() { return getTokens(AUTOMAParser.Star); }
		public TerminalNode Star(int i) {
			return getToken(AUTOMAParser.Star, i);
		}
		public List<TerminalNode> Div() { return getTokens(AUTOMAParser.Div); }
		public TerminalNode Div(int i) {
			return getToken(AUTOMAParser.Div, i);
		}
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
	}

	public final TermContext term() throws RecognitionException {
		TermContext _localctx = new TermContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_term);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(179);
			factor();
			setState(184);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Star || _la==Div) {
				{
				{
				setState(180);
				_la = _input.LA(1);
				if ( !(_la==Star || _la==Div) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(181);
				factor();
				}
				}
				setState(186);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FactorContext extends ParserRuleContext {
		public TerminalNode LeftParen() { return getToken(AUTOMAParser.LeftParen, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RightParen() { return getToken(AUTOMAParser.RightParen, 0); }
		public ExpressionAtomContext expressionAtom() {
			return getRuleContext(ExpressionAtomContext.class,0);
		}
		public FactorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_factor; }
	}

	public final FactorContext factor() throws RecognitionException {
		FactorContext _localctx = new FactorContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_factor);
		try {
			setState(192);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(187);
				match(LeftParen);
				setState(188);
				expression();
				setState(189);
				match(RightParen);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(191);
				expressionAtom();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionAtomContext extends ParserRuleContext {
		public GraphCallContext graphCall() {
			return getRuleContext(GraphCallContext.class,0);
		}
		public VarContext var() {
			return getRuleContext(VarContext.class,0);
		}
		public LiteralsContext literals() {
			return getRuleContext(LiteralsContext.class,0);
		}
		public DataTypesContext dataTypes() {
			return getRuleContext(DataTypesContext.class,0);
		}
		public ExpressionAtomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressionAtom; }
	}

	public final ExpressionAtomContext expressionAtom() throws RecognitionException {
		ExpressionAtomContext _localctx = new ExpressionAtomContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_expressionAtom);
		try {
			setState(198);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(194);
				graphCall();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(195);
				var();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(196);
				literals();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(197);
				dataTypes();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DataTypesContext extends ParserRuleContext {
		public MemoryTypeContext memoryType() {
			return getRuleContext(MemoryTypeContext.class,0);
		}
		public TupleTypeContext tupleType() {
			return getRuleContext(TupleTypeContext.class,0);
		}
		public ListTypeContext listType() {
			return getRuleContext(ListTypeContext.class,0);
		}
		public DataTypesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_dataTypes; }
	}

	public final DataTypesContext dataTypes() throws RecognitionException {
		DataTypesContext _localctx = new DataTypesContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_dataTypes);
		try {
			setState(203);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LeftBrace:
				enterOuterAlt(_localctx, 1);
				{
				setState(200);
				memoryType();
				}
				break;
			case LeftParen:
				enterOuterAlt(_localctx, 2);
				{
				setState(201);
				tupleType();
				}
				break;
			case LeftBracket:
				enterOuterAlt(_localctx, 3);
				{
				setState(202);
				listType();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MemoryTypeContext extends ParserRuleContext {
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public List<TerminalNode> IDENTIFIER() { return getTokens(AUTOMAParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(AUTOMAParser.IDENTIFIER, i);
		}
		public List<TerminalNode> Colon() { return getTokens(AUTOMAParser.Colon); }
		public TerminalNode Colon(int i) {
			return getToken(AUTOMAParser.Colon, i);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(AUTOMAParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(AUTOMAParser.Comma, i);
		}
		public MemoryTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_memoryType; }
	}

	public final MemoryTypeContext memoryType() throws RecognitionException {
		MemoryTypeContext _localctx = new MemoryTypeContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_memoryType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(205);
			match(LeftBrace);
			setState(218);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(206);
				match(IDENTIFIER);
				setState(207);
				match(Colon);
				setState(208);
				expression();
				setState(215);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==Comma) {
					{
					{
					setState(209);
					match(Comma);
					setState(210);
					match(IDENTIFIER);
					setState(211);
					match(Colon);
					setState(212);
					expression();
					}
					}
					setState(217);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(220);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TupleTypeContext extends ParserRuleContext {
		public TerminalNode LeftParen() { return getToken(AUTOMAParser.LeftParen, 0); }
		public TerminalNode RightParen() { return getToken(AUTOMAParser.RightParen, 0); }
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(AUTOMAParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(AUTOMAParser.Comma, i);
		}
		public TupleTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tupleType; }
	}

	public final TupleTypeContext tupleType() throws RecognitionException {
		TupleTypeContext _localctx = new TupleTypeContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_tupleType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(222);
			match(LeftParen);
			setState(233);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 3307348178239488L) != 0)) {
				{
				{
				setState(223);
				expression();
				setState(228);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==Comma) {
					{
					{
					setState(224);
					match(Comma);
					setState(225);
					expression();
					}
					}
					setState(230);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				}
				setState(235);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(236);
			match(RightParen);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ListTypeContext extends ParserRuleContext {
		public TerminalNode LeftBracket() { return getToken(AUTOMAParser.LeftBracket, 0); }
		public TerminalNode RightBracket() { return getToken(AUTOMAParser.RightBracket, 0); }
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(AUTOMAParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(AUTOMAParser.Comma, i);
		}
		public ListTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_listType; }
	}

	public final ListTypeContext listType() throws RecognitionException {
		ListTypeContext _localctx = new ListTypeContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_listType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(238);
			match(LeftBracket);
			setState(249);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 3307348178239488L) != 0)) {
				{
				{
				setState(239);
				expression();
				setState(244);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==Comma) {
					{
					{
					setState(240);
					match(Comma);
					setState(241);
					expression();
					}
					}
					setState(246);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				}
				setState(251);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(252);
			match(RightBracket);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class NodeDefTypesContext extends ParserRuleContext {
		public TerminalNode StartNode() { return getToken(AUTOMAParser.StartNode, 0); }
		public TerminalNode AcceptNode() { return getToken(AUTOMAParser.AcceptNode, 0); }
		public TerminalNode RejectNode() { return getToken(AUTOMAParser.RejectNode, 0); }
		public NodeDefTypesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nodeDefTypes; }
	}

	public final NodeDefTypesContext nodeDefTypes() throws RecognitionException {
		NodeDefTypesContext _localctx = new NodeDefTypesContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_nodeDefTypes);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(254);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 229376L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class GraphCallContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public TupleTypeContext tupleType() {
			return getRuleContext(TupleTypeContext.class,0);
		}
		public GraphCallContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_graphCall; }
	}

	public final GraphCallContext graphCall() throws RecognitionException {
		GraphCallContext _localctx = new GraphCallContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_graphCall);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(256);
			match(IDENTIFIER);
			setState(257);
			tupleType();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AfterAcceptDefinitionContext extends ParserRuleContext {
		public TerminalNode AfterAccept() { return getToken(AUTOMAParser.AfterAccept, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> Semicolon() { return getTokens(AUTOMAParser.Semicolon); }
		public TerminalNode Semicolon(int i) {
			return getToken(AUTOMAParser.Semicolon, i);
		}
		public AfterAcceptDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_afterAcceptDefinition; }
	}

	public final AfterAcceptDefinitionContext afterAcceptDefinition() throws RecognitionException {
		AfterAcceptDefinitionContext _localctx = new AfterAcceptDefinitionContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_afterAcceptDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(259);
			match(AfterAccept);
			setState(260);
			match(LeftBrace);
			setState(266);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 3307348178239488L) != 0)) {
				{
				{
				setState(261);
				expression();
				setState(262);
				match(Semicolon);
				}
				}
				setState(268);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(269);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AfterRejectDefinitionContext extends ParserRuleContext {
		public TerminalNode AfterReject() { return getToken(AUTOMAParser.AfterReject, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> Semicolon() { return getTokens(AUTOMAParser.Semicolon); }
		public TerminalNode Semicolon(int i) {
			return getToken(AUTOMAParser.Semicolon, i);
		}
		public AfterRejectDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_afterRejectDefinition; }
	}

	public final AfterRejectDefinitionContext afterRejectDefinition() throws RecognitionException {
		AfterRejectDefinitionContext _localctx = new AfterRejectDefinitionContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_afterRejectDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(271);
			match(AfterReject);
			setState(272);
			match(LeftBrace);
			setState(278);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 3307348178239488L) != 0)) {
				{
				{
				setState(273);
				expression();
				setState(274);
				match(Semicolon);
				}
				}
				setState(280);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(281);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArithmeticOperatorContext extends ParserRuleContext {
		public TerminalNode Plus() { return getToken(AUTOMAParser.Plus, 0); }
		public TerminalNode Div() { return getToken(AUTOMAParser.Div, 0); }
		public TerminalNode Minus() { return getToken(AUTOMAParser.Minus, 0); }
		public TerminalNode Star() { return getToken(AUTOMAParser.Star, 0); }
		public ArithmeticOperatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arithmeticOperator; }
	}

	public final ArithmeticOperatorContext arithmeticOperator() throws RecognitionException {
		ArithmeticOperatorContext _localctx = new ArithmeticOperatorContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_arithmeticOperator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(283);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 1006632960L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BoolOperatorContext extends ParserRuleContext {
		public TerminalNode And() { return getToken(AUTOMAParser.And, 0); }
		public TerminalNode Or() { return getToken(AUTOMAParser.Or, 0); }
		public TerminalNode Equal() { return getToken(AUTOMAParser.Equal, 0); }
		public BoolOperatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_boolOperator; }
	}

	public final BoolOperatorContext boolOperator() throws RecognitionException {
		BoolOperatorContext _localctx = new BoolOperatorContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_boolOperator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(285);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 281320357888L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LiteralsContext extends ParserRuleContext {
		public BooleanLiteralContext booleanLiteral() {
			return getRuleContext(BooleanLiteralContext.class,0);
		}
		public CharLiteralContext charLiteral() {
			return getRuleContext(CharLiteralContext.class,0);
		}
		public StringLiteralContext stringLiteral() {
			return getRuleContext(StringLiteralContext.class,0);
		}
		public IntegerLiteralContext integerLiteral() {
			return getRuleContext(IntegerLiteralContext.class,0);
		}
		public LiteralsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literals; }
	}

	public final LiteralsContext literals() throws RecognitionException {
		LiteralsContext _localctx = new LiteralsContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_literals);
		try {
			setState(291);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BooleanLiteral:
				enterOuterAlt(_localctx, 1);
				{
				setState(287);
				booleanLiteral();
				}
				break;
			case CharLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(288);
				charLiteral();
				}
				break;
			case StringLiteral:
				enterOuterAlt(_localctx, 3);
				{
				setState(289);
				stringLiteral();
				}
				break;
			case IntegerLiteral:
				enterOuterAlt(_localctx, 4);
				{
				setState(290);
				integerLiteral();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VarContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public VarContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var; }
	}

	public final VarContext var() throws RecognitionException {
		VarContext _localctx = new VarContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_var);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(293);
			match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BooleanLiteralContext extends ParserRuleContext {
		public TerminalNode BooleanLiteral() { return getToken(AUTOMAParser.BooleanLiteral, 0); }
		public BooleanLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_booleanLiteral; }
	}

	public final BooleanLiteralContext booleanLiteral() throws RecognitionException {
		BooleanLiteralContext _localctx = new BooleanLiteralContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_booleanLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(295);
			match(BooleanLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StringLiteralContext extends ParserRuleContext {
		public TerminalNode StringLiteral() { return getToken(AUTOMAParser.StringLiteral, 0); }
		public StringLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stringLiteral; }
	}

	public final StringLiteralContext stringLiteral() throws RecognitionException {
		StringLiteralContext _localctx = new StringLiteralContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_stringLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(297);
			match(StringLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CharLiteralContext extends ParserRuleContext {
		public TerminalNode CharLiteral() { return getToken(AUTOMAParser.CharLiteral, 0); }
		public CharLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_charLiteral; }
	}

	public final CharLiteralContext charLiteral() throws RecognitionException {
		CharLiteralContext _localctx = new CharLiteralContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_charLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(299);
			match(CharLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IntegerLiteralContext extends ParserRuleContext {
		public TerminalNode IntegerLiteral() { return getToken(AUTOMAParser.IntegerLiteral, 0); }
		public IntegerLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_integerLiteral; }
	}

	public final IntegerLiteralContext integerLiteral() throws RecognitionException {
		IntegerLiteralContext _localctx = new IntegerLiteralContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_integerLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(301);
			match(IntegerLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DigitContext extends ParserRuleContext {
		public TerminalNode Digit() { return getToken(AUTOMAParser.Digit, 0); }
		public DigitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_digit; }
	}

	public final DigitContext digit() throws RecognitionException {
		DigitContext _localctx = new DigitContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_digit);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(303);
			match(Digit);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u00017\u0132\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007\u001b"+
		"\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002\u001e\u0007\u001e"+
		"\u0002\u001f\u0007\u001f\u0001\u0000\u0005\u0000B\b\u0000\n\u0000\f\u0000"+
		"E\t\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0005\u0002"+
		"Q\b\u0002\n\u0002\f\u0002T\t\u0002\u0001\u0002\u0005\u0002W\b\u0002\n"+
		"\u0002\f\u0002Z\t\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0005\u0003"+
		"e\b\u0003\n\u0003\f\u0003h\t\u0003\u0003\u0003j\b\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0005"+
		"\u0004y\b\u0004\n\u0004\f\u0004|\t\u0004\u0003\u0004~\b\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0004\u0005\u0085\b\u0005"+
		"\u000b\u0005\f\u0005\u0086\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007"+
		"\u0001\b\u0001\b\u0001\t\u0005\t\u009c\b\t\n\t\f\t\u009f\t\t\u0001\t\u0001"+
		"\t\u0001\n\u0001\n\u0001\n\u0001\n\u0005\n\u00a7\b\n\n\n\f\n\u00aa\t\n"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0005\u000b\u00af\b\u000b\n\u000b"+
		"\f\u000b\u00b2\t\u000b\u0001\f\u0001\f\u0001\f\u0005\f\u00b7\b\f\n\f\f"+
		"\f\u00ba\t\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0003\r\u00c1\b\r"+
		"\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0003\u000e\u00c7\b\u000e"+
		"\u0001\u000f\u0001\u000f\u0001\u000f\u0003\u000f\u00cc\b\u000f\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010"+
		"\u0001\u0010\u0005\u0010\u00d6\b\u0010\n\u0010\f\u0010\u00d9\t\u0010\u0003"+
		"\u0010\u00db\b\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0005\u0011\u00e3\b\u0011\n\u0011\f\u0011\u00e6\t\u0011"+
		"\u0005\u0011\u00e8\b\u0011\n\u0011\f\u0011\u00eb\t\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0005\u0012\u00f3"+
		"\b\u0012\n\u0012\f\u0012\u00f6\t\u0012\u0005\u0012\u00f8\b\u0012\n\u0012"+
		"\f\u0012\u00fb\t\u0012\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0015\u0001\u0015\u0001\u0015"+
		"\u0001\u0015\u0001\u0015\u0005\u0015\u0109\b\u0015\n\u0015\f\u0015\u010c"+
		"\t\u0015\u0001\u0015\u0001\u0015\u0001\u0016\u0001\u0016\u0001\u0016\u0001"+
		"\u0016\u0001\u0016\u0005\u0016\u0115\b\u0016\n\u0016\f\u0016\u0118\t\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0017\u0001\u0017\u0001\u0018\u0001\u0018"+
		"\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u0019\u0003\u0019\u0124\b\u0019"+
		"\u0001\u001a\u0001\u001a\u0001\u001b\u0001\u001b\u0001\u001c\u0001\u001c"+
		"\u0001\u001d\u0001\u001d\u0001\u001e\u0001\u001e\u0001\u001f\u0001\u001f"+
		"\u0001\u001f\u0000\u0000 \u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012"+
		"\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,.02468:<>\u0000\u0005\u0001"+
		"\u0000\u001a\u001b\u0001\u0000\u001c\u001d\u0001\u0000\u000f\u0011\u0001"+
		"\u0000\u001a\u001d\u0002\u0000\u001f &&\u012e\u0000C\u0001\u0000\u0000"+
		"\u0000\u0002F\u0001\u0000\u0000\u0000\u0004L\u0001\u0000\u0000\u0000\u0006"+
		"[\u0001\u0000\u0000\u0000\bm\u0001\u0000\u0000\u0000\n\u0081\u0001\u0000"+
		"\u0000\u0000\f\u008a\u0001\u0000\u0000\u0000\u000e\u0096\u0001\u0000\u0000"+
		"\u0000\u0010\u0098\u0001\u0000\u0000\u0000\u0012\u009d\u0001\u0000\u0000"+
		"\u0000\u0014\u00a2\u0001\u0000\u0000\u0000\u0016\u00ab\u0001\u0000\u0000"+
		"\u0000\u0018\u00b3\u0001\u0000\u0000\u0000\u001a\u00c0\u0001\u0000\u0000"+
		"\u0000\u001c\u00c6\u0001\u0000\u0000\u0000\u001e\u00cb\u0001\u0000\u0000"+
		"\u0000 \u00cd\u0001\u0000\u0000\u0000\"\u00de\u0001\u0000\u0000\u0000"+
		"$\u00ee\u0001\u0000\u0000\u0000&\u00fe\u0001\u0000\u0000\u0000(\u0100"+
		"\u0001\u0000\u0000\u0000*\u0103\u0001\u0000\u0000\u0000,\u010f\u0001\u0000"+
		"\u0000\u0000.\u011b\u0001\u0000\u0000\u00000\u011d\u0001\u0000\u0000\u0000"+
		"2\u0123\u0001\u0000\u0000\u00004\u0125\u0001\u0000\u0000\u00006\u0127"+
		"\u0001\u0000\u0000\u00008\u0129\u0001\u0000\u0000\u0000:\u012b\u0001\u0000"+
		"\u0000\u0000<\u012d\u0001\u0000\u0000\u0000>\u012f\u0001\u0000\u0000\u0000"+
		"@B\u0003\u0002\u0001\u0000A@\u0001\u0000\u0000\u0000BE\u0001\u0000\u0000"+
		"\u0000CA\u0001\u0000\u0000\u0000CD\u0001\u0000\u0000\u0000D\u0001\u0001"+
		"\u0000\u0000\u0000EC\u0001\u0000\u0000\u0000FG\u0005\u0003\u0000\u0000"+
		"GH\u00053\u0000\u0000HI\u0005\u0018\u0000\u0000IJ\u0003\u0004\u0002\u0000"+
		"JK\u0005\u0019\u0000\u0000K\u0003\u0001\u0000\u0000\u0000LM\u0003\u0006"+
		"\u0003\u0000MN\u0003\b\u0004\u0000NR\u0003\n\u0005\u0000OQ\u0003*\u0015"+
		"\u0000PO\u0001\u0000\u0000\u0000QT\u0001\u0000\u0000\u0000RP\u0001\u0000"+
		"\u0000\u0000RS\u0001\u0000\u0000\u0000SX\u0001\u0000\u0000\u0000TR\u0001"+
		"\u0000\u0000\u0000UW\u0003,\u0016\u0000VU\u0001\u0000\u0000\u0000WZ\u0001"+
		"\u0000\u0000\u0000XV\u0001\u0000\u0000\u0000XY\u0001\u0000\u0000\u0000"+
		"Y\u0005\u0001\u0000\u0000\u0000ZX\u0001\u0000\u0000\u0000[\\\u0005\u0004"+
		"\u0000\u0000\\i\u0005\u0018\u0000\u0000]^\u00053\u0000\u0000^_\u0005,"+
		"\u0000\u0000_f\u0003\u0012\t\u0000`a\u0005-\u0000\u0000ab\u00053\u0000"+
		"\u0000bc\u0005,\u0000\u0000ce\u0003\u0012\t\u0000d`\u0001\u0000\u0000"+
		"\u0000eh\u0001\u0000\u0000\u0000fd\u0001\u0000\u0000\u0000fg\u0001\u0000"+
		"\u0000\u0000gj\u0001\u0000\u0000\u0000hf\u0001\u0000\u0000\u0000i]\u0001"+
		"\u0000\u0000\u0000ij\u0001\u0000\u0000\u0000jk\u0001\u0000\u0000\u0000"+
		"kl\u0005\u0019\u0000\u0000l\u0007\u0001\u0000\u0000\u0000mn\u0005\u000e"+
		"\u0000\u0000n}\u0005\u0018\u0000\u0000op\u00053\u0000\u0000pq\u0005+\u0000"+
		"\u0000qr\u0003&\u0013\u0000rz\u0005*\u0000\u0000st\u00053\u0000\u0000"+
		"tu\u0005+\u0000\u0000uv\u0003&\u0013\u0000vw\u0005*\u0000\u0000wy\u0001"+
		"\u0000\u0000\u0000xs\u0001\u0000\u0000\u0000y|\u0001\u0000\u0000\u0000"+
		"zx\u0001\u0000\u0000\u0000z{\u0001\u0000\u0000\u0000{~\u0001\u0000\u0000"+
		"\u0000|z\u0001\u0000\u0000\u0000}o\u0001\u0000\u0000\u0000}~\u0001\u0000"+
		"\u0000\u0000~\u007f\u0001\u0000\u0000\u0000\u007f\u0080\u0005\u0019\u0000"+
		"\u0000\u0080\t\u0001\u0000\u0000\u0000\u0081\u0082\u0005\u0002\u0000\u0000"+
		"\u0082\u0084\u0005\u0018\u0000\u0000\u0083\u0085\u0003\f\u0006\u0000\u0084"+
		"\u0083\u0001\u0000\u0000\u0000\u0085\u0086\u0001\u0000\u0000\u0000\u0086"+
		"\u0084\u0001\u0000\u0000\u0000\u0086\u0087\u0001\u0000\u0000\u0000\u0087"+
		"\u0088\u0001\u0000\u0000\u0000\u0088\u0089\u0005\u0019\u0000\u0000\u0089"+
		"\u000b\u0001\u0000\u0000\u0000\u008a\u008b\u0003\u000e\u0007\u0000\u008b"+
		"\u008c\u0003\u0010\b\u0000\u008c\u008d\u0005\u0013\u0000\u0000\u008d\u008e"+
		"\u0005\u000b\u0000\u0000\u008e\u008f\u0005,\u0000\u0000\u008f\u0090\u0003"+
		"\"\u0011\u0000\u0090\u0091\u0005-\u0000\u0000\u0091\u0092\u0005\f\u0000"+
		"\u0000\u0092\u0093\u0005,\u0000\u0000\u0093\u0094\u0003\"\u0011\u0000"+
		"\u0094\u0095\u0005*\u0000\u0000\u0095\r\u0001\u0000\u0000\u0000\u0096"+
		"\u0097\u00053\u0000\u0000\u0097\u000f\u0001\u0000\u0000\u0000\u0098\u0099"+
		"\u00053\u0000\u0000\u0099\u0011\u0001\u0000\u0000\u0000\u009a\u009c\u0005"+
		"\"\u0000\u0000\u009b\u009a\u0001\u0000\u0000\u0000\u009c\u009f\u0001\u0000"+
		"\u0000\u0000\u009d\u009b\u0001\u0000\u0000\u0000\u009d\u009e\u0001\u0000"+
		"\u0000\u0000\u009e\u00a0\u0001\u0000\u0000\u0000\u009f\u009d\u0001\u0000"+
		"\u0000\u0000\u00a0\u00a1\u0003\u0014\n\u0000\u00a1\u0013\u0001\u0000\u0000"+
		"\u0000\u00a2\u00a8\u0003\u0016\u000b\u0000\u00a3\u00a4\u00030\u0018\u0000"+
		"\u00a4\u00a5\u0003\u0016\u000b\u0000\u00a5\u00a7\u0001\u0000\u0000\u0000"+
		"\u00a6\u00a3\u0001\u0000\u0000\u0000\u00a7\u00aa\u0001\u0000\u0000\u0000"+
		"\u00a8\u00a6\u0001\u0000\u0000\u0000\u00a8\u00a9\u0001\u0000\u0000\u0000"+
		"\u00a9\u0015\u0001\u0000\u0000\u0000\u00aa\u00a8\u0001\u0000\u0000\u0000"+
		"\u00ab\u00b0\u0003\u0018\f\u0000\u00ac\u00ad\u0007\u0000\u0000\u0000\u00ad"+
		"\u00af\u0003\u0018\f\u0000\u00ae\u00ac\u0001\u0000\u0000\u0000\u00af\u00b2"+
		"\u0001\u0000\u0000\u0000\u00b0\u00ae\u0001\u0000\u0000\u0000\u00b0\u00b1"+
		"\u0001\u0000\u0000\u0000\u00b1\u0017\u0001\u0000\u0000\u0000\u00b2\u00b0"+
		"\u0001\u0000\u0000\u0000\u00b3\u00b8\u0003\u001a\r\u0000\u00b4\u00b5\u0007"+
		"\u0001\u0000\u0000\u00b5\u00b7\u0003\u001a\r\u0000\u00b6\u00b4\u0001\u0000"+
		"\u0000\u0000\u00b7\u00ba\u0001\u0000\u0000\u0000\u00b8\u00b6\u0001\u0000"+
		"\u0000\u0000\u00b8\u00b9\u0001\u0000\u0000\u0000\u00b9\u0019\u0001\u0000"+
		"\u0000\u0000\u00ba\u00b8\u0001\u0000\u0000\u0000\u00bb\u00bc\u0005\u0014"+
		"\u0000\u0000\u00bc\u00bd\u0003\u0012\t\u0000\u00bd\u00be\u0005\u0015\u0000"+
		"\u0000\u00be\u00c1\u0001\u0000\u0000\u0000\u00bf\u00c1\u0003\u001c\u000e"+
		"\u0000\u00c0\u00bb\u0001\u0000\u0000\u0000\u00c0\u00bf\u0001\u0000\u0000"+
		"\u0000\u00c1\u001b\u0001\u0000\u0000\u0000\u00c2\u00c7\u0003(\u0014\u0000"+
		"\u00c3\u00c7\u00034\u001a\u0000\u00c4\u00c7\u00032\u0019\u0000\u00c5\u00c7"+
		"\u0003\u001e\u000f\u0000\u00c6\u00c2\u0001\u0000\u0000\u0000\u00c6\u00c3"+
		"\u0001\u0000\u0000\u0000\u00c6\u00c4\u0001\u0000\u0000\u0000\u00c6\u00c5"+
		"\u0001\u0000\u0000\u0000\u00c7\u001d\u0001\u0000\u0000\u0000\u00c8\u00cc"+
		"\u0003 \u0010\u0000\u00c9\u00cc\u0003\"\u0011\u0000\u00ca\u00cc\u0003"+
		"$\u0012\u0000\u00cb\u00c8\u0001\u0000\u0000\u0000\u00cb\u00c9\u0001\u0000"+
		"\u0000\u0000\u00cb\u00ca\u0001\u0000\u0000\u0000\u00cc\u001f\u0001\u0000"+
		"\u0000\u0000\u00cd\u00da\u0005\u0018\u0000\u0000\u00ce\u00cf\u00053\u0000"+
		"\u0000\u00cf\u00d0\u0005,\u0000\u0000\u00d0\u00d7\u0003\u0012\t\u0000"+
		"\u00d1\u00d2\u0005-\u0000\u0000\u00d2\u00d3\u00053\u0000\u0000\u00d3\u00d4"+
		"\u0005,\u0000\u0000\u00d4\u00d6\u0003\u0012\t\u0000\u00d5\u00d1\u0001"+
		"\u0000\u0000\u0000\u00d6\u00d9\u0001\u0000\u0000\u0000\u00d7\u00d5\u0001"+
		"\u0000\u0000\u0000\u00d7\u00d8\u0001\u0000\u0000\u0000\u00d8\u00db\u0001"+
		"\u0000\u0000\u0000\u00d9\u00d7\u0001\u0000\u0000\u0000\u00da\u00ce\u0001"+
		"\u0000\u0000\u0000\u00da\u00db\u0001\u0000\u0000\u0000\u00db\u00dc\u0001"+
		"\u0000\u0000\u0000\u00dc\u00dd\u0005\u0019\u0000\u0000\u00dd!\u0001\u0000"+
		"\u0000\u0000\u00de\u00e9\u0005\u0014\u0000\u0000\u00df\u00e4\u0003\u0012"+
		"\t\u0000\u00e0\u00e1\u0005-\u0000\u0000\u00e1\u00e3\u0003\u0012\t\u0000"+
		"\u00e2\u00e0\u0001\u0000\u0000\u0000\u00e3\u00e6\u0001\u0000\u0000\u0000"+
		"\u00e4\u00e2\u0001\u0000\u0000\u0000\u00e4\u00e5\u0001\u0000\u0000\u0000"+
		"\u00e5\u00e8\u0001\u0000\u0000\u0000\u00e6\u00e4\u0001\u0000\u0000\u0000"+
		"\u00e7\u00df\u0001\u0000\u0000\u0000\u00e8\u00eb\u0001\u0000\u0000\u0000"+
		"\u00e9\u00e7\u0001\u0000\u0000\u0000\u00e9\u00ea\u0001\u0000\u0000\u0000"+
		"\u00ea\u00ec\u0001\u0000\u0000\u0000\u00eb\u00e9\u0001\u0000\u0000\u0000"+
		"\u00ec\u00ed\u0005\u0015\u0000\u0000\u00ed#\u0001\u0000\u0000\u0000\u00ee"+
		"\u00f9\u0005\u0016\u0000\u0000\u00ef\u00f4\u0003\u0012\t\u0000\u00f0\u00f1"+
		"\u0005-\u0000\u0000\u00f1\u00f3\u0003\u0012\t\u0000\u00f2\u00f0\u0001"+
		"\u0000\u0000\u0000\u00f3\u00f6\u0001\u0000\u0000\u0000\u00f4\u00f2\u0001"+
		"\u0000\u0000\u0000\u00f4\u00f5\u0001\u0000\u0000\u0000\u00f5\u00f8\u0001"+
		"\u0000\u0000\u0000\u00f6\u00f4\u0001\u0000\u0000\u0000\u00f7\u00ef\u0001"+
		"\u0000\u0000\u0000\u00f8\u00fb\u0001\u0000\u0000\u0000\u00f9\u00f7\u0001"+
		"\u0000\u0000\u0000\u00f9\u00fa\u0001\u0000\u0000\u0000\u00fa\u00fc\u0001"+
		"\u0000\u0000\u0000\u00fb\u00f9\u0001\u0000\u0000\u0000\u00fc\u00fd\u0005"+
		"\u0017\u0000\u0000\u00fd%\u0001\u0000\u0000\u0000\u00fe\u00ff\u0007\u0002"+
		"\u0000\u0000\u00ff\'\u0001\u0000\u0000\u0000\u0100\u0101\u00053\u0000"+
		"\u0000\u0101\u0102\u0003\"\u0011\u0000\u0102)\u0001\u0000\u0000\u0000"+
		"\u0103\u0104\u0005\u0006\u0000\u0000\u0104\u010a\u0005\u0018\u0000\u0000"+
		"\u0105\u0106\u0003\u0012\t\u0000\u0106\u0107\u0005*\u0000\u0000\u0107"+
		"\u0109\u0001\u0000\u0000\u0000\u0108\u0105\u0001\u0000\u0000\u0000\u0109"+
		"\u010c\u0001\u0000\u0000\u0000\u010a\u0108\u0001\u0000\u0000\u0000\u010a"+
		"\u010b\u0001\u0000\u0000\u0000\u010b\u010d\u0001\u0000\u0000\u0000\u010c"+
		"\u010a\u0001\u0000\u0000\u0000\u010d\u010e\u0005\u0019\u0000\u0000\u010e"+
		"+\u0001\u0000\u0000\u0000\u010f\u0110\u0005\u0005\u0000\u0000\u0110\u0116"+
		"\u0005\u0018\u0000\u0000\u0111\u0112\u0003\u0012\t\u0000\u0112\u0113\u0005"+
		"*\u0000\u0000\u0113\u0115\u0001\u0000\u0000\u0000\u0114\u0111\u0001\u0000"+
		"\u0000\u0000\u0115\u0118\u0001\u0000\u0000\u0000\u0116\u0114\u0001\u0000"+
		"\u0000\u0000\u0116\u0117\u0001\u0000\u0000\u0000\u0117\u0119\u0001\u0000"+
		"\u0000\u0000\u0118\u0116\u0001\u0000\u0000\u0000\u0119\u011a\u0005\u0019"+
		"\u0000\u0000\u011a-\u0001\u0000\u0000\u0000\u011b\u011c\u0007\u0003\u0000"+
		"\u0000\u011c/\u0001\u0000\u0000\u0000\u011d\u011e\u0007\u0004\u0000\u0000"+
		"\u011e1\u0001\u0000\u0000\u0000\u011f\u0124\u00036\u001b\u0000\u0120\u0124"+
		"\u0003:\u001d\u0000\u0121\u0124\u00038\u001c\u0000\u0122\u0124\u0003<"+
		"\u001e\u0000\u0123\u011f\u0001\u0000\u0000\u0000\u0123\u0120\u0001\u0000"+
		"\u0000\u0000\u0123\u0121\u0001\u0000\u0000\u0000\u0123\u0122\u0001\u0000"+
		"\u0000\u0000\u01243\u0001\u0000\u0000\u0000\u0125\u0126\u00053\u0000\u0000"+
		"\u01265\u0001\u0000\u0000\u0000\u0127\u0128\u0005.\u0000\u0000\u01287"+
		"\u0001\u0000\u0000\u0000\u0129\u012a\u0005/\u0000\u0000\u012a9\u0001\u0000"+
		"\u0000\u0000\u012b\u012c\u00050\u0000\u0000\u012c;\u0001\u0000\u0000\u0000"+
		"\u012d\u012e\u00051\u0000\u0000\u012e=\u0001\u0000\u0000\u0000\u012f\u0130"+
		"\u00052\u0000\u0000\u0130?\u0001\u0000\u0000\u0000\u0018CRXfiz}\u0086"+
		"\u009d\u00a8\u00b0\u00b8\u00c0\u00c6\u00cb\u00d7\u00da\u00e4\u00e9\u00f4"+
		"\u00f9\u010a\u0116\u0123";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}