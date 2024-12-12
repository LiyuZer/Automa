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
		Operator=1, Transition=2, Start=3, Accept=4, Node=5, Graph=6, Memory=7, 
		AfterReject=8, AfterAccept=9, Symbols=10, Array=11, Dict=12, Tuple=13, 
		Conditions=14, Operations=15, None=16, Arrow=17, ArrowEquals=18, LeftParen=19, 
		RightParen=20, LeftBracket=21, RightBracket=22, LeftBrace=23, RightBrace=24, 
		Plus=25, Minus=26, Star=27, Div=28, Mod=29, And=30, Or=31, Tilde=32, Not=33, 
		Assign=34, Less=35, Greater=36, Equal=37, NotEqual=38, LessEqual=39, GreaterEqual=40, 
		AndAnd=41, OrOr=42, Semicolon=43, Colon=44, Comma=45, BooleanLiteral=46, 
		StringLiteral=47, CharLiteral=48, IntegerLiteral=49, Digit=50, IDENTIFIER=51, 
		Whitespace=52, Newline=53, BlockComment=54, LineComment=55;
	public static final int
		RULE_r = 0, RULE_graphDef = 1, RULE_graphBody = 2, RULE_memory = 3, RULE_nodeDefinitions = 4, 
		RULE_transitionsDef = 5, RULE_afterAcceptStatement = 6, RULE_afterRejectStatement = 7, 
		RULE_fromNode = 8, RULE_toNode = 9, RULE_conditionsData = 10, RULE_operationsData = 11, 
		RULE_dataType = 12, RULE_arrayData = 13, RULE_symbolsData = 14, RULE_dictData = 15, 
		RULE_tupleData = 16, RULE_keyValuePairList = 17, RULE_arrayElemList = 18, 
		RULE_dictElemData = 19, RULE_keyValuePair = 20, RULE_elemType = 21, RULE_identifier = 22, 
		RULE_integerLiteral = 23, RULE_stringLiteral = 24, RULE_charLiteral = 25, 
		RULE_booleanLiteral = 26;
	private static String[] makeRuleNames() {
		return new String[] {
			"r", "graphDef", "graphBody", "memory", "nodeDefinitions", "transitionsDef", 
			"afterAcceptStatement", "afterRejectStatement", "fromNode", "toNode", 
			"conditionsData", "operationsData", "dataType", "arrayData", "symbolsData", 
			"dictData", "tupleData", "keyValuePairList", "arrayElemList", "dictElemData", 
			"keyValuePair", "elemType", "identifier", "integerLiteral", "stringLiteral", 
			"charLiteral", "booleanLiteral"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'operator'", "'transition'", "'start'", "'accept'", "'node'", 
			"'graph'", "'memory'", "'afterReject'", "'afterAccept'", "'symbols'", 
			"'array'", "'dict'", "'tuple'", "'conditions'", "'operations'", "'None'", 
			"'->'", "'=>'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'+'", "'-'", 
			"'*'", "'/'", "'%'", "'&'", "'|'", "'~'", null, "'='", "'<'", "'>'", 
			"'=='", "'!='", "'<='", "'>='", null, null, "';'", "':'", "','"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "Operator", "Transition", "Start", "Accept", "Node", "Graph", "Memory", 
			"AfterReject", "AfterAccept", "Symbols", "Array", "Dict", "Tuple", "Conditions", 
			"Operations", "None", "Arrow", "ArrowEquals", "LeftParen", "RightParen", 
			"LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "Plus", "Minus", 
			"Star", "Div", "Mod", "And", "Or", "Tilde", "Not", "Assign", "Less", 
			"Greater", "Equal", "NotEqual", "LessEqual", "GreaterEqual", "AndAnd", 
			"OrOr", "Semicolon", "Colon", "Comma", "BooleanLiteral", "StringLiteral", 
			"CharLiteral", "IntegerLiteral", "Digit", "IDENTIFIER", "Whitespace", 
			"Newline", "BlockComment", "LineComment"
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
			setState(57);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Graph) {
				{
				{
				setState(54);
				graphDef();
				}
				}
				setState(59);
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
			setState(60);
			match(Graph);
			setState(61);
			match(IDENTIFIER);
			setState(62);
			match(LeftBrace);
			setState(63);
			graphBody();
			setState(64);
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
		public List<MemoryContext> memory() {
			return getRuleContexts(MemoryContext.class);
		}
		public MemoryContext memory(int i) {
			return getRuleContext(MemoryContext.class,i);
		}
		public List<NodeDefinitionsContext> nodeDefinitions() {
			return getRuleContexts(NodeDefinitionsContext.class);
		}
		public NodeDefinitionsContext nodeDefinitions(int i) {
			return getRuleContext(NodeDefinitionsContext.class,i);
		}
		public List<TransitionsDefContext> transitionsDef() {
			return getRuleContexts(TransitionsDefContext.class);
		}
		public TransitionsDefContext transitionsDef(int i) {
			return getRuleContext(TransitionsDefContext.class,i);
		}
		public List<AfterAcceptStatementContext> afterAcceptStatement() {
			return getRuleContexts(AfterAcceptStatementContext.class);
		}
		public AfterAcceptStatementContext afterAcceptStatement(int i) {
			return getRuleContext(AfterAcceptStatementContext.class,i);
		}
		public List<AfterRejectStatementContext> afterRejectStatement() {
			return getRuleContexts(AfterRejectStatementContext.class);
		}
		public AfterRejectStatementContext afterRejectStatement(int i) {
			return getRuleContext(AfterRejectStatementContext.class,i);
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
			setState(69);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Memory) {
				{
				{
				setState(66);
				memory();
				}
				}
				setState(71);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(75);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Node) {
				{
				{
				setState(72);
				nodeDefinitions();
				}
				}
				setState(77);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(81);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Transition) {
				{
				{
				setState(78);
				transitionsDef();
				}
				}
				setState(83);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(87);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==AfterAccept) {
				{
				{
				setState(84);
				afterAcceptStatement();
				}
				}
				setState(89);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(93);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==AfterReject) {
				{
				{
				setState(90);
				afterRejectStatement();
				}
				}
				setState(95);
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
	public static class MemoryContext extends ParserRuleContext {
		public TerminalNode Memory() { return getToken(AUTOMAParser.Memory, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public KeyValuePairListContext keyValuePairList() {
			return getRuleContext(KeyValuePairListContext.class,0);
		}
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public MemoryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_memory; }
	}

	public final MemoryContext memory() throws RecognitionException {
		MemoryContext _localctx = new MemoryContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_memory);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(96);
			match(Memory);
			setState(97);
			match(LeftBrace);
			setState(98);
			keyValuePairList();
			setState(99);
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
	public static class NodeDefinitionsContext extends ParserRuleContext {
		public TerminalNode Node() { return getToken(AUTOMAParser.Node, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public List<TerminalNode> IDENTIFIER() { return getTokens(AUTOMAParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(AUTOMAParser.IDENTIFIER, i);
		}
		public List<TerminalNode> Semicolon() { return getTokens(AUTOMAParser.Semicolon); }
		public TerminalNode Semicolon(int i) {
			return getToken(AUTOMAParser.Semicolon, i);
		}
		public NodeDefinitionsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nodeDefinitions; }
	}

	public final NodeDefinitionsContext nodeDefinitions() throws RecognitionException {
		NodeDefinitionsContext _localctx = new NodeDefinitionsContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_nodeDefinitions);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(101);
			match(Node);
			setState(102);
			match(LeftBrace);
			setState(105); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(103);
				match(IDENTIFIER);
				setState(104);
				match(Semicolon);
				}
				}
				setState(107); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==IDENTIFIER );
			setState(109);
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
	public static class TransitionsDefContext extends ParserRuleContext {
		public TerminalNode Transition() { return getToken(AUTOMAParser.Transition, 0); }
		public TerminalNode Arrow() { return getToken(AUTOMAParser.Arrow, 0); }
		public FromNodeContext fromNode() {
			return getRuleContext(FromNodeContext.class,0);
		}
		public ToNodeContext toNode() {
			return getRuleContext(ToNodeContext.class,0);
		}
		public TerminalNode ArrowEquals() { return getToken(AUTOMAParser.ArrowEquals, 0); }
		public TerminalNode Conditions() { return getToken(AUTOMAParser.Conditions, 0); }
		public List<TerminalNode> Colon() { return getTokens(AUTOMAParser.Colon); }
		public TerminalNode Colon(int i) {
			return getToken(AUTOMAParser.Colon, i);
		}
		public ConditionsDataContext conditionsData() {
			return getRuleContext(ConditionsDataContext.class,0);
		}
		public TerminalNode Comma() { return getToken(AUTOMAParser.Comma, 0); }
		public TerminalNode Operations() { return getToken(AUTOMAParser.Operations, 0); }
		public OperationsDataContext operationsData() {
			return getRuleContext(OperationsDataContext.class,0);
		}
		public TerminalNode Semicolon() { return getToken(AUTOMAParser.Semicolon, 0); }
		public TransitionsDefContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_transitionsDef; }
	}

	public final TransitionsDefContext transitionsDef() throws RecognitionException {
		TransitionsDefContext _localctx = new TransitionsDefContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_transitionsDef);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(111);
			match(Transition);
			setState(112);
			match(Arrow);
			setState(113);
			fromNode();
			setState(114);
			toNode();
			setState(115);
			match(ArrowEquals);
			setState(116);
			match(Conditions);
			setState(117);
			match(Colon);
			setState(118);
			conditionsData();
			setState(119);
			match(Comma);
			setState(120);
			match(Operations);
			setState(121);
			match(Colon);
			setState(122);
			operationsData();
			setState(123);
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
	public static class AfterAcceptStatementContext extends ParserRuleContext {
		public TerminalNode AfterAccept() { return getToken(AUTOMAParser.AfterAccept, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public AfterAcceptStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_afterAcceptStatement; }
	}

	public final AfterAcceptStatementContext afterAcceptStatement() throws RecognitionException {
		AfterAcceptStatementContext _localctx = new AfterAcceptStatementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_afterAcceptStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(125);
			match(AfterAccept);
			setState(126);
			match(LeftBrace);
			setState(127);
			match(IDENTIFIER);
			setState(128);
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
	public static class AfterRejectStatementContext extends ParserRuleContext {
		public TerminalNode AfterReject() { return getToken(AUTOMAParser.AfterReject, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public AfterRejectStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_afterRejectStatement; }
	}

	public final AfterRejectStatementContext afterRejectStatement() throws RecognitionException {
		AfterRejectStatementContext _localctx = new AfterRejectStatementContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_afterRejectStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(130);
			match(AfterReject);
			setState(131);
			match(LeftBrace);
			setState(132);
			match(IDENTIFIER);
			setState(133);
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
	public static class FromNodeContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public FromNodeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fromNode; }
	}

	public final FromNodeContext fromNode() throws RecognitionException {
		FromNodeContext _localctx = new FromNodeContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_fromNode);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(135);
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
	public static class ToNodeContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public ToNodeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_toNode; }
	}

	public final ToNodeContext toNode() throws RecognitionException {
		ToNodeContext _localctx = new ToNodeContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_toNode);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(137);
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
	public static class ConditionsDataContext extends ParserRuleContext {
		public TupleDataContext tupleData() {
			return getRuleContext(TupleDataContext.class,0);
		}
		public ConditionsDataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_conditionsData; }
	}

	public final ConditionsDataContext conditionsData() throws RecognitionException {
		ConditionsDataContext _localctx = new ConditionsDataContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_conditionsData);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(139);
			tupleData();
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
	public static class OperationsDataContext extends ParserRuleContext {
		public TupleDataContext tupleData() {
			return getRuleContext(TupleDataContext.class,0);
		}
		public OperationsDataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_operationsData; }
	}

	public final OperationsDataContext operationsData() throws RecognitionException {
		OperationsDataContext _localctx = new OperationsDataContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_operationsData);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(141);
			tupleData();
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
	public static class DataTypeContext extends ParserRuleContext {
		public DictDataContext dictData() {
			return getRuleContext(DictDataContext.class,0);
		}
		public ArrayDataContext arrayData() {
			return getRuleContext(ArrayDataContext.class,0);
		}
		public SymbolsDataContext symbolsData() {
			return getRuleContext(SymbolsDataContext.class,0);
		}
		public TupleDataContext tupleData() {
			return getRuleContext(TupleDataContext.class,0);
		}
		public DataTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_dataType; }
	}

	public final DataTypeContext dataType() throws RecognitionException {
		DataTypeContext _localctx = new DataTypeContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_dataType);
		try {
			setState(147);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Dict:
			case LeftBrace:
				enterOuterAlt(_localctx, 1);
				{
				setState(143);
				dictData();
				}
				break;
			case Array:
			case LeftBracket:
				enterOuterAlt(_localctx, 2);
				{
				setState(144);
				arrayData();
				}
				break;
			case Symbols:
				enterOuterAlt(_localctx, 3);
				{
				setState(145);
				symbolsData();
				}
				break;
			case Tuple:
			case LeftParen:
				enterOuterAlt(_localctx, 4);
				{
				setState(146);
				tupleData();
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
	public static class ArrayDataContext extends ParserRuleContext {
		public TerminalNode LeftBracket() { return getToken(AUTOMAParser.LeftBracket, 0); }
		public ArrayElemListContext arrayElemList() {
			return getRuleContext(ArrayElemListContext.class,0);
		}
		public TerminalNode RightBracket() { return getToken(AUTOMAParser.RightBracket, 0); }
		public TerminalNode Array() { return getToken(AUTOMAParser.Array, 0); }
		public TerminalNode Arrow() { return getToken(AUTOMAParser.Arrow, 0); }
		public ArrayDataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayData; }
	}

	public final ArrayDataContext arrayData() throws RecognitionException {
		ArrayDataContext _localctx = new ArrayDataContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_arrayData);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(151);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Array) {
				{
				setState(149);
				match(Array);
				setState(150);
				match(Arrow);
				}
			}

			setState(153);
			match(LeftBracket);
			setState(154);
			arrayElemList();
			setState(155);
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
	public static class SymbolsDataContext extends ParserRuleContext {
		public TerminalNode Symbols() { return getToken(AUTOMAParser.Symbols, 0); }
		public TerminalNode Arrow() { return getToken(AUTOMAParser.Arrow, 0); }
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public KeyValuePairListContext keyValuePairList() {
			return getRuleContext(KeyValuePairListContext.class,0);
		}
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public SymbolsDataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_symbolsData; }
	}

	public final SymbolsDataContext symbolsData() throws RecognitionException {
		SymbolsDataContext _localctx = new SymbolsDataContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_symbolsData);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(157);
			match(Symbols);
			setState(158);
			match(Arrow);
			setState(159);
			match(LeftBrace);
			setState(160);
			keyValuePairList();
			setState(161);
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
	public static class DictDataContext extends ParserRuleContext {
		public TerminalNode LeftBrace() { return getToken(AUTOMAParser.LeftBrace, 0); }
		public KeyValuePairListContext keyValuePairList() {
			return getRuleContext(KeyValuePairListContext.class,0);
		}
		public TerminalNode RightBrace() { return getToken(AUTOMAParser.RightBrace, 0); }
		public TerminalNode Dict() { return getToken(AUTOMAParser.Dict, 0); }
		public TerminalNode Arrow() { return getToken(AUTOMAParser.Arrow, 0); }
		public DictDataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_dictData; }
	}

	public final DictDataContext dictData() throws RecognitionException {
		DictDataContext _localctx = new DictDataContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_dictData);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(165);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Dict) {
				{
				setState(163);
				match(Dict);
				setState(164);
				match(Arrow);
				}
			}

			setState(167);
			match(LeftBrace);
			setState(168);
			keyValuePairList();
			setState(169);
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
	public static class TupleDataContext extends ParserRuleContext {
		public TerminalNode LeftParen() { return getToken(AUTOMAParser.LeftParen, 0); }
		public ArrayElemListContext arrayElemList() {
			return getRuleContext(ArrayElemListContext.class,0);
		}
		public TerminalNode RightParen() { return getToken(AUTOMAParser.RightParen, 0); }
		public TerminalNode Tuple() { return getToken(AUTOMAParser.Tuple, 0); }
		public TerminalNode Arrow() { return getToken(AUTOMAParser.Arrow, 0); }
		public TupleDataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tupleData; }
	}

	public final TupleDataContext tupleData() throws RecognitionException {
		TupleDataContext _localctx = new TupleDataContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_tupleData);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(173);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Tuple) {
				{
				setState(171);
				match(Tuple);
				setState(172);
				match(Arrow);
				}
			}

			setState(175);
			match(LeftParen);
			setState(176);
			arrayElemList();
			setState(177);
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
	public static class KeyValuePairListContext extends ParserRuleContext {
		public DictElemDataContext dictElemData() {
			return getRuleContext(DictElemDataContext.class,0);
		}
		public KeyValuePairListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_keyValuePairList; }
	}

	public final KeyValuePairListContext keyValuePairList() throws RecognitionException {
		KeyValuePairListContext _localctx = new KeyValuePairListContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_keyValuePairList);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(179);
			dictElemData();
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
	public static class ArrayElemListContext extends ParserRuleContext {
		public List<ElemTypeContext> elemType() {
			return getRuleContexts(ElemTypeContext.class);
		}
		public ElemTypeContext elemType(int i) {
			return getRuleContext(ElemTypeContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(AUTOMAParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(AUTOMAParser.Comma, i);
		}
		public ArrayElemListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayElemList; }
	}

	public final ArrayElemListContext arrayElemList() throws RecognitionException {
		ArrayElemListContext _localctx = new ArrayElemListContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_arrayElemList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(181);
			elemType();
			setState(186);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(182);
				match(Comma);
				setState(183);
				elemType();
				}
				}
				setState(188);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
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
	public static class DictElemDataContext extends ParserRuleContext {
		public List<KeyValuePairContext> keyValuePair() {
			return getRuleContexts(KeyValuePairContext.class);
		}
		public KeyValuePairContext keyValuePair(int i) {
			return getRuleContext(KeyValuePairContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(AUTOMAParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(AUTOMAParser.Comma, i);
		}
		public DictElemDataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_dictElemData; }
	}

	public final DictElemDataContext dictElemData() throws RecognitionException {
		DictElemDataContext _localctx = new DictElemDataContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_dictElemData);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(189);
			keyValuePair();
			setState(194);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(190);
				match(Comma);
				setState(191);
				keyValuePair();
				}
				}
				setState(196);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
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
	public static class KeyValuePairContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public TerminalNode Colon() { return getToken(AUTOMAParser.Colon, 0); }
		public ElemTypeContext elemType() {
			return getRuleContext(ElemTypeContext.class,0);
		}
		public KeyValuePairContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_keyValuePair; }
	}

	public final KeyValuePairContext keyValuePair() throws RecognitionException {
		KeyValuePairContext _localctx = new KeyValuePairContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_keyValuePair);
		try {
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(197);
			match(IDENTIFIER);
			setState(198);
			match(Colon);
			setState(199);
			elemType();
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
	public static class ElemTypeContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public IntegerLiteralContext integerLiteral() {
			return getRuleContext(IntegerLiteralContext.class,0);
		}
		public StringLiteralContext stringLiteral() {
			return getRuleContext(StringLiteralContext.class,0);
		}
		public CharLiteralContext charLiteral() {
			return getRuleContext(CharLiteralContext.class,0);
		}
		public BooleanLiteralContext booleanLiteral() {
			return getRuleContext(BooleanLiteralContext.class,0);
		}
		public ElemTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elemType; }
	}

	public final ElemTypeContext elemType() throws RecognitionException {
		ElemTypeContext _localctx = new ElemTypeContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_elemType);
		try {
			setState(206);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(201);
				identifier();
				}
				break;
			case IntegerLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(202);
				integerLiteral();
				}
				break;
			case StringLiteral:
				enterOuterAlt(_localctx, 3);
				{
				setState(203);
				stringLiteral();
				}
				break;
			case CharLiteral:
				enterOuterAlt(_localctx, 4);
				{
				setState(204);
				charLiteral();
				}
				break;
			case BooleanLiteral:
				enterOuterAlt(_localctx, 5);
				{
				setState(205);
				booleanLiteral();
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
	public static class IdentifierContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(AUTOMAParser.IDENTIFIER, 0); }
		public IdentifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identifier; }
	}

	public final IdentifierContext identifier() throws RecognitionException {
		IdentifierContext _localctx = new IdentifierContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_identifier);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(208);
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
	public static class IntegerLiteralContext extends ParserRuleContext {
		public TerminalNode IntegerLiteral() { return getToken(AUTOMAParser.IntegerLiteral, 0); }
		public IntegerLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_integerLiteral; }
	}

	public final IntegerLiteralContext integerLiteral() throws RecognitionException {
		IntegerLiteralContext _localctx = new IntegerLiteralContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_integerLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(210);
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
	public static class StringLiteralContext extends ParserRuleContext {
		public TerminalNode StringLiteral() { return getToken(AUTOMAParser.StringLiteral, 0); }
		public StringLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stringLiteral; }
	}

	public final StringLiteralContext stringLiteral() throws RecognitionException {
		StringLiteralContext _localctx = new StringLiteralContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_stringLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(212);
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
		enterRule(_localctx, 50, RULE_charLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(214);
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
	public static class BooleanLiteralContext extends ParserRuleContext {
		public TerminalNode BooleanLiteral() { return getToken(AUTOMAParser.BooleanLiteral, 0); }
		public BooleanLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_booleanLiteral; }
	}

	public final BooleanLiteralContext booleanLiteral() throws RecognitionException {
		BooleanLiteralContext _localctx = new BooleanLiteralContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_booleanLiteral);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(216);
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

	public static final String _serializedATN =
		"\u0004\u00017\u00db\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0001\u0000\u0005\u0000"+
		"8\b\u0000\n\u0000\f\u0000;\t\u0000\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0002\u0005\u0002D\b\u0002"+
		"\n\u0002\f\u0002G\t\u0002\u0001\u0002\u0005\u0002J\b\u0002\n\u0002\f\u0002"+
		"M\t\u0002\u0001\u0002\u0005\u0002P\b\u0002\n\u0002\f\u0002S\t\u0002\u0001"+
		"\u0002\u0005\u0002V\b\u0002\n\u0002\f\u0002Y\t\u0002\u0001\u0002\u0005"+
		"\u0002\\\b\u0002\n\u0002\f\u0002_\t\u0002\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0004\u0004j\b\u0004\u000b\u0004\f\u0004k\u0001\u0004\u0001\u0004"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\b\u0001\b\u0001\t\u0001\t\u0001\n\u0001\n\u0001\u000b\u0001\u000b"+
		"\u0001\f\u0001\f\u0001\f\u0001\f\u0003\f\u0094\b\f\u0001\r\u0001\r\u0003"+
		"\r\u0098\b\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000f\u0001\u000f\u0003"+
		"\u000f\u00a6\b\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001"+
		"\u0010\u0001\u0010\u0003\u0010\u00ae\b\u0010\u0001\u0010\u0001\u0010\u0001"+
		"\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0005\u0012\u00b9\b\u0012\n\u0012\f\u0012\u00bc\t\u0012\u0001\u0013"+
		"\u0001\u0013\u0001\u0013\u0005\u0013\u00c1\b\u0013\n\u0013\f\u0013\u00c4"+
		"\t\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0015\u0001"+
		"\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0003\u0015\u00cf\b\u0015\u0001"+
		"\u0016\u0001\u0016\u0001\u0017\u0001\u0017\u0001\u0018\u0001\u0018\u0001"+
		"\u0019\u0001\u0019\u0001\u001a\u0001\u001a\u0001\u001a\u0000\u0000\u001b"+
		"\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a"+
		"\u001c\u001e \"$&(*,.024\u0000\u0000\u00d2\u00009\u0001\u0000\u0000\u0000"+
		"\u0002<\u0001\u0000\u0000\u0000\u0004E\u0001\u0000\u0000\u0000\u0006`"+
		"\u0001\u0000\u0000\u0000\be\u0001\u0000\u0000\u0000\no\u0001\u0000\u0000"+
		"\u0000\f}\u0001\u0000\u0000\u0000\u000e\u0082\u0001\u0000\u0000\u0000"+
		"\u0010\u0087\u0001\u0000\u0000\u0000\u0012\u0089\u0001\u0000\u0000\u0000"+
		"\u0014\u008b\u0001\u0000\u0000\u0000\u0016\u008d\u0001\u0000\u0000\u0000"+
		"\u0018\u0093\u0001\u0000\u0000\u0000\u001a\u0097\u0001\u0000\u0000\u0000"+
		"\u001c\u009d\u0001\u0000\u0000\u0000\u001e\u00a5\u0001\u0000\u0000\u0000"+
		" \u00ad\u0001\u0000\u0000\u0000\"\u00b3\u0001\u0000\u0000\u0000$\u00b5"+
		"\u0001\u0000\u0000\u0000&\u00bd\u0001\u0000\u0000\u0000(\u00c5\u0001\u0000"+
		"\u0000\u0000*\u00ce\u0001\u0000\u0000\u0000,\u00d0\u0001\u0000\u0000\u0000"+
		".\u00d2\u0001\u0000\u0000\u00000\u00d4\u0001\u0000\u0000\u00002\u00d6"+
		"\u0001\u0000\u0000\u00004\u00d8\u0001\u0000\u0000\u000068\u0003\u0002"+
		"\u0001\u000076\u0001\u0000\u0000\u00008;\u0001\u0000\u0000\u000097\u0001"+
		"\u0000\u0000\u00009:\u0001\u0000\u0000\u0000:\u0001\u0001\u0000\u0000"+
		"\u0000;9\u0001\u0000\u0000\u0000<=\u0005\u0006\u0000\u0000=>\u00053\u0000"+
		"\u0000>?\u0005\u0017\u0000\u0000?@\u0003\u0004\u0002\u0000@A\u0005\u0018"+
		"\u0000\u0000A\u0003\u0001\u0000\u0000\u0000BD\u0003\u0006\u0003\u0000"+
		"CB\u0001\u0000\u0000\u0000DG\u0001\u0000\u0000\u0000EC\u0001\u0000\u0000"+
		"\u0000EF\u0001\u0000\u0000\u0000FK\u0001\u0000\u0000\u0000GE\u0001\u0000"+
		"\u0000\u0000HJ\u0003\b\u0004\u0000IH\u0001\u0000\u0000\u0000JM\u0001\u0000"+
		"\u0000\u0000KI\u0001\u0000\u0000\u0000KL\u0001\u0000\u0000\u0000LQ\u0001"+
		"\u0000\u0000\u0000MK\u0001\u0000\u0000\u0000NP\u0003\n\u0005\u0000ON\u0001"+
		"\u0000\u0000\u0000PS\u0001\u0000\u0000\u0000QO\u0001\u0000\u0000\u0000"+
		"QR\u0001\u0000\u0000\u0000RW\u0001\u0000\u0000\u0000SQ\u0001\u0000\u0000"+
		"\u0000TV\u0003\f\u0006\u0000UT\u0001\u0000\u0000\u0000VY\u0001\u0000\u0000"+
		"\u0000WU\u0001\u0000\u0000\u0000WX\u0001\u0000\u0000\u0000X]\u0001\u0000"+
		"\u0000\u0000YW\u0001\u0000\u0000\u0000Z\\\u0003\u000e\u0007\u0000[Z\u0001"+
		"\u0000\u0000\u0000\\_\u0001\u0000\u0000\u0000][\u0001\u0000\u0000\u0000"+
		"]^\u0001\u0000\u0000\u0000^\u0005\u0001\u0000\u0000\u0000_]\u0001\u0000"+
		"\u0000\u0000`a\u0005\u0007\u0000\u0000ab\u0005\u0017\u0000\u0000bc\u0003"+
		"\"\u0011\u0000cd\u0005\u0018\u0000\u0000d\u0007\u0001\u0000\u0000\u0000"+
		"ef\u0005\u0005\u0000\u0000fi\u0005\u0017\u0000\u0000gh\u00053\u0000\u0000"+
		"hj\u0005+\u0000\u0000ig\u0001\u0000\u0000\u0000jk\u0001\u0000\u0000\u0000"+
		"ki\u0001\u0000\u0000\u0000kl\u0001\u0000\u0000\u0000lm\u0001\u0000\u0000"+
		"\u0000mn\u0005\u0018\u0000\u0000n\t\u0001\u0000\u0000\u0000op\u0005\u0002"+
		"\u0000\u0000pq\u0005\u0011\u0000\u0000qr\u0003\u0010\b\u0000rs\u0003\u0012"+
		"\t\u0000st\u0005\u0012\u0000\u0000tu\u0005\u000e\u0000\u0000uv\u0005,"+
		"\u0000\u0000vw\u0003\u0014\n\u0000wx\u0005-\u0000\u0000xy\u0005\u000f"+
		"\u0000\u0000yz\u0005,\u0000\u0000z{\u0003\u0016\u000b\u0000{|\u0005+\u0000"+
		"\u0000|\u000b\u0001\u0000\u0000\u0000}~\u0005\t\u0000\u0000~\u007f\u0005"+
		"\u0017\u0000\u0000\u007f\u0080\u00053\u0000\u0000\u0080\u0081\u0005\u0018"+
		"\u0000\u0000\u0081\r\u0001\u0000\u0000\u0000\u0082\u0083\u0005\b\u0000"+
		"\u0000\u0083\u0084\u0005\u0017\u0000\u0000\u0084\u0085\u00053\u0000\u0000"+
		"\u0085\u0086\u0005\u0018\u0000\u0000\u0086\u000f\u0001\u0000\u0000\u0000"+
		"\u0087\u0088\u00053\u0000\u0000\u0088\u0011\u0001\u0000\u0000\u0000\u0089"+
		"\u008a\u00053\u0000\u0000\u008a\u0013\u0001\u0000\u0000\u0000\u008b\u008c"+
		"\u0003 \u0010\u0000\u008c\u0015\u0001\u0000\u0000\u0000\u008d\u008e\u0003"+
		" \u0010\u0000\u008e\u0017\u0001\u0000\u0000\u0000\u008f\u0094\u0003\u001e"+
		"\u000f\u0000\u0090\u0094\u0003\u001a\r\u0000\u0091\u0094\u0003\u001c\u000e"+
		"\u0000\u0092\u0094\u0003 \u0010\u0000\u0093\u008f\u0001\u0000\u0000\u0000"+
		"\u0093\u0090\u0001\u0000\u0000\u0000\u0093\u0091\u0001\u0000\u0000\u0000"+
		"\u0093\u0092\u0001\u0000\u0000\u0000\u0094\u0019\u0001\u0000\u0000\u0000"+
		"\u0095\u0096\u0005\u000b\u0000\u0000\u0096\u0098\u0005\u0011\u0000\u0000"+
		"\u0097\u0095\u0001\u0000\u0000\u0000\u0097\u0098\u0001\u0000\u0000\u0000"+
		"\u0098\u0099\u0001\u0000\u0000\u0000\u0099\u009a\u0005\u0015\u0000\u0000"+
		"\u009a\u009b\u0003$\u0012\u0000\u009b\u009c\u0005\u0016\u0000\u0000\u009c"+
		"\u001b\u0001\u0000\u0000\u0000\u009d\u009e\u0005\n\u0000\u0000\u009e\u009f"+
		"\u0005\u0011\u0000\u0000\u009f\u00a0\u0005\u0017\u0000\u0000\u00a0\u00a1"+
		"\u0003\"\u0011\u0000\u00a1\u00a2\u0005\u0018\u0000\u0000\u00a2\u001d\u0001"+
		"\u0000\u0000\u0000\u00a3\u00a4\u0005\f\u0000\u0000\u00a4\u00a6\u0005\u0011"+
		"\u0000\u0000\u00a5\u00a3\u0001\u0000\u0000\u0000\u00a5\u00a6\u0001\u0000"+
		"\u0000\u0000\u00a6\u00a7\u0001\u0000\u0000\u0000\u00a7\u00a8\u0005\u0017"+
		"\u0000\u0000\u00a8\u00a9\u0003\"\u0011\u0000\u00a9\u00aa\u0005\u0018\u0000"+
		"\u0000\u00aa\u001f\u0001\u0000\u0000\u0000\u00ab\u00ac\u0005\r\u0000\u0000"+
		"\u00ac\u00ae\u0005\u0011\u0000\u0000\u00ad\u00ab\u0001\u0000\u0000\u0000"+
		"\u00ad\u00ae\u0001\u0000\u0000\u0000\u00ae\u00af\u0001\u0000\u0000\u0000"+
		"\u00af\u00b0\u0005\u0013\u0000\u0000\u00b0\u00b1\u0003$\u0012\u0000\u00b1"+
		"\u00b2\u0005\u0014\u0000\u0000\u00b2!\u0001\u0000\u0000\u0000\u00b3\u00b4"+
		"\u0003&\u0013\u0000\u00b4#\u0001\u0000\u0000\u0000\u00b5\u00ba\u0003*"+
		"\u0015\u0000\u00b6\u00b7\u0005-\u0000\u0000\u00b7\u00b9\u0003*\u0015\u0000"+
		"\u00b8\u00b6\u0001\u0000\u0000\u0000\u00b9\u00bc\u0001\u0000\u0000\u0000"+
		"\u00ba\u00b8\u0001\u0000\u0000\u0000\u00ba\u00bb\u0001\u0000\u0000\u0000"+
		"\u00bb%\u0001\u0000\u0000\u0000\u00bc\u00ba\u0001\u0000\u0000\u0000\u00bd"+
		"\u00c2\u0003(\u0014\u0000\u00be\u00bf\u0005-\u0000\u0000\u00bf\u00c1\u0003"+
		"(\u0014\u0000\u00c0\u00be\u0001\u0000\u0000\u0000\u00c1\u00c4\u0001\u0000"+
		"\u0000\u0000\u00c2\u00c0\u0001\u0000\u0000\u0000\u00c2\u00c3\u0001\u0000"+
		"\u0000\u0000\u00c3\'\u0001\u0000\u0000\u0000\u00c4\u00c2\u0001\u0000\u0000"+
		"\u0000\u00c5\u00c6\u00053\u0000\u0000\u00c6\u00c7\u0005,\u0000\u0000\u00c7"+
		"\u00c8\u0003*\u0015\u0000\u00c8)\u0001\u0000\u0000\u0000\u00c9\u00cf\u0003"+
		",\u0016\u0000\u00ca\u00cf\u0003.\u0017\u0000\u00cb\u00cf\u00030\u0018"+
		"\u0000\u00cc\u00cf\u00032\u0019\u0000\u00cd\u00cf\u00034\u001a\u0000\u00ce"+
		"\u00c9\u0001\u0000\u0000\u0000\u00ce\u00ca\u0001\u0000\u0000\u0000\u00ce"+
		"\u00cb\u0001\u0000\u0000\u0000\u00ce\u00cc\u0001\u0000\u0000\u0000\u00ce"+
		"\u00cd\u0001\u0000\u0000\u0000\u00cf+\u0001\u0000\u0000\u0000\u00d0\u00d1"+
		"\u00053\u0000\u0000\u00d1-\u0001\u0000\u0000\u0000\u00d2\u00d3\u00051"+
		"\u0000\u0000\u00d3/\u0001\u0000\u0000\u0000\u00d4\u00d5\u0005/\u0000\u0000"+
		"\u00d51\u0001\u0000\u0000\u0000\u00d6\u00d7\u00050\u0000\u0000\u00d73"+
		"\u0001\u0000\u0000\u0000\u00d8\u00d9\u0005.\u0000\u0000\u00d95\u0001\u0000"+
		"\u0000\u0000\u000e9EKQW]k\u0093\u0097\u00a5\u00ad\u00ba\u00c2\u00ce";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}