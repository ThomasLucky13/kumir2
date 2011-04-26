#ifndef AST_STATEMENT_H
#define AST_STATEMENT_H

#include <QList>

#undef ABSTRACTSYNTAXTREE_EXPORT
#ifdef ABSTRACTSYNTAXTREE_LIBRARY
#define ABSTRACTSYNTAXTREE_EXPORT Q_DECL_EXPORT
#else
#define ABSTRACTSYNTAXTREE_EXPORT Q_DECL_IMPORT
#endif

namespace AST {

/** Defines statement (in terminology of Kumir 1.x: ProgaValue) type */
enum StatementType {

    /** No actual statement, but error code */
    StError,

    /** Assignment of function call
      * NOTE: function call is "assignment", where left part is void */
    StAssign,

    /** Assert, pre-condition of post-condition,
      * depending on context */
    StAssert,

    /** Array-variable initialization */
    StVarInitialize,

    /** Terminal input */
    StInput,

    /** Terminal output */
    StOutput,

    /** File input */
    StFileInput,

    /** File output */
    StFileOutput,

    /** Loop block */
    StLoop,

    /** One or two if-then-else sub-blocks */
    StIfThenElse,

    /** At lease one switch-case-else sub-block */
    StSwitchCaseElse,

    /** Loop break of function return statement */
    StBreak
};

/** Loop clarification */
enum LoopType {

    /** For loop (russian: "nc dlja") */
    LoopFor,

    /** While or forever loop (russian: "nc" or "nc poka") */
    LoopWhile,

    /** Counter loop (russian "nc ? raz") */
    LoopTimes,
};

/** Loop-specific part of statement */
struct LoopSpec {

    /** Loop type */
    enum LoopType type;

    /** Referece to "for" loop variable */
    struct Variable * forVariable;

    /** "for" loop "from" value */
    struct Expression * fromValue;

    /** "for" loop "to" value */
    struct Expression * toValue;

    /** "for" loop "step" value */
    struct Expression * stepValue;

    /** "while" loop condition value */
    struct Expression * whileCondition;

    /** "times" loop value */
    struct Expression * timesValue;

    /** Optional condition for loop end */
    struct Expression * endCondition;

    /** Loop body */
    QList<struct Statement * > body;

    /** Loop end line number in source program */
    int endLineNo;
};

/** "if-then", "case" or "else" sub-block of statement */
struct ConditionSpec {

    /** Condition; empty for "else" block */
    struct Expression * condition;

    /** Conditional body */
    QList<struct Statement * > body;

    /** Block begin line number in source program */
    int startLineNo;
};

/** Evaluable statement */
struct ABSTRACTSYNTAXTREE_EXPORT Statement {

    /** Statement kind */
    StatementType type;

    /** Line number in source program */
    int lineNo;

    /** Compile-time error code */
    int error;

    /** List of top-level expressions for all
      * statement kinds except StLoop, StIfThenElse and StSwitchCaseElse */
    QList<struct Expression * > expressions;

    /** Variable references list, defined only if type==StVarInitialize */
    QList<struct Variable * > variables;

    /** Loop specific-part, defined only if type==StLoop */
    struct LoopSpec loop;

    /** Conditional blocks, defined only if type==StIfThenElse or type==StSwitchCaseElse */
    QList<struct ConditionSpec> conditionals;

    explicit Statement();
    explicit Statement(const struct Statement * src);
    void updateReferences(const struct Statement * src,
                          const struct Data * srcData,
                          const struct Data * data);
    ~Statement();
};


}

#endif // AST_STATEMENT_H
