#include "VASTVisitor.h"

using namespace std;
using namespace vast;

namespace vastvisitor {
  VAST* VASTVisitor::visitSpec(VParser::SpecContext *ctx) {
    if (ctx->behavioralSpec()) {
      return visitBehavioralSpec(ctx->behavioralSpec());
    } else if (ctx->testSpec()) {
      return visitTestSpec(ctx->testSpec());
    } else if (ctx->tempSpec()) {
      return visitTempSpec(ctx->tempSpec());
    }

    return nullptr;
  }

  VBehavioralSpec* VASTVisitor::visitBehavioralSpec(VParser::BehavioralSpecContext *ctx) {
    VVarDeclList* var_decs = nullptr;
    VStatementExpr* pre = nullptr;
    if (ctx->varsSection()) {
      var_decs = visitVarsSection(ctx->varsSection());
    }
    if (ctx->precondSection()) {
      pre = visitPrecondSection(ctx->precondSection());
    }
    VStatementExpr* post = visitPostcondSection(ctx->postcondSection());
    return new VBehavioralSpec(var_decs, pre, post);
  }

  VTestSpec* VASTVisitor::visitTestSpec(VParser::TestSpecContext *ctx) {
    VVarDeclList* var_decs = nullptr;
    vector<VStatementExpr*> init;
    if (ctx->varsSection()) {
      var_decs = visitVarsSection(ctx->varsSection());
    }
    if (ctx->initSection()) {
      init = visitInitSection(ctx->initSection());
    }
    vector<VStatementExpr*> spec = visitSpecSection(ctx->specSection());
    return new VTestSpec(var_decs, init, spec);
  }

  VTempSpec* VASTVisitor::visitTempSpec(VParser::TempSpecContext *ctx) {
    VVarDeclList* var_decs = nullptr;
    VStatementExpr* fairness;
    if (ctx->varsSection()) {
      var_decs = visitVarsSection(ctx->varsSection());
    }
    if (ctx->ltlFairnessSection()) {
      fairness = visitLtlFairnessSection(ctx->ltlFairnessSection());
    }
    VStatementExpr* prop = visitLtlPropertySection(ctx->ltlPropertySection());
    return new VTempSpec(var_decs, fairness, prop);
  }

  VVarDeclList* VASTVisitor::visitVarsSection(VParser::VarsSectionContext *ctx) {
    return visitDeclList(ctx->declList());
  }

  vector<VStatementExpr*> VASTVisitor::visitInitSection(VParser::InitSectionContext *ctx) {
    return visitSeqAtom(ctx->seqAtom());
  }

  vector<VStatementExpr*> VASTVisitor::visitSpecSection(VParser::SpecSectionContext *ctx) {
    return visitSeqAtom(ctx->seqAtom());
  }

  VStatementExpr* VASTVisitor::visitLtlFairnessSection(VParser::LtlFairnessSectionContext *ctx) {
    return visitSmartltlAtom(ctx->smartltlAtom());
  }

  VStatementExpr* VASTVisitor::visitLtlPropertySection(VParser::LtlPropertySectionContext *ctx) {
    return visitSmartltlAtom(ctx->smartltlAtom());
  }

  VStatementExpr* VASTVisitor::visitSmartltlAtom(VParser::SmartltlAtomContext *ctx) {
    if (ctx->atom()) {
      return visitAtom(ctx->atom());
    }

    if (ctx->smartltlAtom().size() > 0) {
      VStatementExpr* s1 = visitSmartltlAtom(ctx->smartltlAtom()[0]);
      if (ctx->T_UN()) {
        VUnOp *op = new VUnOp(ctx->T_UN()->getText());
        return new VUnStatementExpr(s1, op);
      } else if (ctx->L_UN()) {
        VUnOp *op = new VUnOp(ctx->L_UN()->getText());
        return new VUnStatementExpr(s1, op);
      } else if (ctx->LBRACK()) {
        VUnOp *op = new VUnOp("[]");
        return new VUnStatementExpr(s1, op);
      } else if (ctx->smartltlAtom().size() == 2) {
        VStatementExpr* s2 = visitSmartltlAtom(ctx->smartltlAtom()[1]);
        string op_str;
        if (ctx->T_BIN()) {
          op_str = ctx->T_BIN()->getText();
        } else if (ctx->L_BIN()) {
          op_str = ctx->L_BIN()->getText();
        } else if (ctx->SEQ()) {
          op_str = ctx->SEQ()->getText();
        }
        VBinOp *op = new VBinOp(op_str);
        return new VBinStatementExpr(s1, s2, op);
      }
      return s1;
    }

    return nullptr;
  }

  vector<VStatementExpr*> VASTVisitor::visitSeqAtom(VParser::SeqAtomContext *ctx) {
    vector<VStatementExpr*> statements;

    VStatementExpr *s1 = visitAtom(ctx->atom());
    statements.push_back(s1);

    if (ctx->seqAtom()) {
      vector<VStatementExpr*> rest = visitSeqAtom(ctx->seqAtom());
      statements.insert(statements.end(), rest.begin(), rest.end());
    }

    return statements;
  }

  VVarDeclList* VASTVisitor::visitDeclList(VParser::DeclListContext *ctx) {
    vector<VType*> typs;
    vector<VID*> vars;
    VType *typ = visitTyp(ctx->typ());
    VID *var = visitIdent(ctx->ident());

    typs.push_back(typ);
    vars.push_back(var);

    if (ctx->declList()) {
      VVarDeclList *restDecs = visitDeclList(ctx->declList());
      typs.insert(typs.end(), restDecs->typs.begin(), restDecs->typs.end());
      vars.insert(vars.end(), restDecs->vars.begin(), restDecs->vars.end());
    }

    return new VVarDeclList(typs, vars);
  }

  VType* VASTVisitor::visitTyp(VParser::TypContext *ctx) {
    string name = ctx->IDENTIFIER()->getText();
    bool is_arr = false;
    if (ctx->LBRACK()) {
      is_arr = true;
    }
    return new VType(name, is_arr);
  }

  VID* VASTVisitor::visitIdent(VParser::IdentContext *ctx) {
    string name;
    if (ctx->IDENTIFIER()) {
      name = ctx->IDENTIFIER()->getText();
    }
    if (ctx->ATOM_LOC()) {
      name = ctx->ATOM_LOC()->getText();
    }
    return new VID(name);
  }

  VStatementExpr* VASTVisitor::visitPostcondSection(VParser::PostcondSectionContext *ctx) {
    return visitAtom(ctx->atom());
  }

  VStatementExpr* VASTVisitor::visitPrecondSection(VParser::PrecondSectionContext *ctx) {
    return visitAtom(ctx->atom());
  }

  VStatementExpr* VASTVisitor::visitAtom(VParser::AtomContext *ctx) {
    if (ctx->ATOM_LOC()) {
      VFunctionID *fun = visitAtomFn(ctx->atomFn());
      string stmt_typ = ctx->ATOM_LOC()->getText();
      VConstraintExpr *con = nullptr;
      if (ctx->constraint()) {
        con = visitConstraint(ctx->constraint());
      }

      if (stmt_typ == "executed") {
        return new VExecutedStatement(fun, con);
      } else if (stmt_typ == "finished") {
        return new VFinishedStatement(fun, con);
      } else if (stmt_typ == "started") {
        return new VStartedStatement(fun, con);
      } else if (stmt_typ == "reverted") {
        return new VRevertedStatement(fun, con);
      } else if (stmt_typ == "willSucceed") {
        return new VWillSucceedStatement(fun, con);
      }
    }

    if (ctx->LET()) {
      // TODO
    }

    if (ctx->FOREACH()) {
      // TODO
    }

    if (ctx->SENT()) {
      // TODO
    }

    if (ctx->atom().size() > 0) {
      VStatementExpr* a1 = visitAtom(ctx->atom()[0]);
      if (ctx->L_UN()) {
        VUnOp *op = new VUnOp(ctx->L_UN()->getText());
        return new VUnStatementExpr(a1, op);
      } else if (ctx->atom().size() == 2) {
        VStatementExpr* a2 = visitAtom(ctx->atom()[1]);
        VBinOp *op = new VBinOp(ctx->L_BIN()->getText());
        return new VBinStatementExpr(a1, a2, op);
      }

      return a1;
    }

    return nullptr;
  }

  VFunctionID* VASTVisitor::visitAtomFn(VParser::AtomFnContext *ctx) {
    VArgList *args = nullptr;
    string name;
    if (ctx->WILDCARD()) {
      name = ctx->WILDCARD()->getText();
    }

    if (ctx->atomFnName()) {
      name = ctx->atomFnName()->getText();
    }

    if (ctx->params()) {
      args = visitParams(ctx->params());
    }

    return new VFunctionID(name, args);
  }

  VArgList* VASTVisitor::visitParams(VParser::ParamsContext *ctx) {
    vector<VConstraintExpr*> args;

    if (ctx->ident()) {
      VID *id = visitIdent(ctx->ident());
      VVarExpr *expr = new VVarExpr(id);
      args.push_back(expr);
    }

    if (ctx->NUM()) {
      VConstExpr *expr = new VConstExpr(ctx->NUM()->getText());
      args.push_back(expr);
    }

    if (ctx->params()) {
      VArgList* rest = visitParams(ctx->params());
      args.insert(args.end(), rest->args.begin(), rest->args.end());
    }

    return new VArgList(args);
  }

  VConstraintExpr* VASTVisitor::visitConstraint(VParser::ConstraintContext *ctx) {
    if (ctx->constraint().size() > 0) {
      VConstraintExpr* c1 = visitConstraint(ctx->constraint()[0]);
      if (ctx->constraint().size() == 2) {
        VConstraintExpr* c2 = visitConstraint(ctx->constraint()[1]);
        VBinOp *op = new VBinOp(ctx->L_BIN()->getText());
        return new VBinExpr(c1, c2, op);
      }

      return c1;
    }

    if (ctx->boolExpr()) {
      return visitBoolExpr(ctx->boolExpr());
    }

    return nullptr;
  }

  VConstraintExpr* VASTVisitor::visitBoolExpr(VParser::BoolExprContext *ctx) {
    if (ctx->boolExpr()) {
      VConstraintExpr* expr = visitBoolExpr(ctx->boolExpr());
      if (ctx->L_UN()) {
        VUnOp *op = new VUnOp(ctx->L_UN()->getText());
        return new VUnExpr(expr, op);
      }

      return expr;
    }

    if (ctx->varOrNum()) {
      return visitVarOrNum(ctx->varOrNum());
    }

    if (ctx->arithExpr().size() > 0) {
      VConstraintExpr *lhs = visitArithExpr(ctx->arithExpr()[0]);
      VConstraintExpr *rhs = visitArithExpr(ctx->arithExpr()[1]);
      VBinOp *op = new VBinOp(ctx->C_BIN()->getText());
      return new VBinExpr(lhs, rhs, op);
    }

    return nullptr;
  }

  VConstraintExpr* VASTVisitor::visitVarOrNum(VParser::VarOrNumContext *ctx) {
    if (ctx->num()) {
      return new VConstExpr(ctx->num()->NUM()->getText());
    }

    if (ctx->varAccess()) {
      return visitVarAccess(ctx->varAccess());
    }

    return nullptr;
  }

  VConstraintExpr* VASTVisitor::visitVarAccess(VParser::VarAccessContext *ctx) {
    if (ctx->varAccess()) {
      VConstraintExpr *var = visitVarAccess(ctx->varAccess());
      if (ctx->LBRACK()) {
        VConstraintExpr *idx = visitArithExpr(ctx->arithExpr());
        return new VArrAccessExpr(var, idx);
      }

      VID *field = visitIdent(ctx->ident());
      return new VFieldAccessExpr(var, field);
    }

    if (ctx->ident()) {
      VID *id = visitIdent(ctx->ident());
      return new VVarExpr(id);
    }

    if (ctx->fnCall()) {
      return visitFnCall(ctx->fnCall());
    }

    return nullptr;
  }

  VConstraintExpr* VASTVisitor::visitFnCall(VParser::FnCallContext *ctx) {
    if (ctx->FSUM()) {
      VFunctionID *func = visitAtomFn(ctx->atomFn());
      VConstraintExpr* arg = visitVarOrNum(ctx->varOrNum());
      VConstraintExpr* con = visitConstraint(ctx->constraint());

      return new VFSumExpr(func, arg, con);
    }

    if (ctx->fnName()) {
      string func = ctx->fnName()->getText();
      VArgList *args = visitArgList(ctx->argList());

      return new VFuncCallExpr(func, args);
    }

    return nullptr;
  }

  VArgList* VASTVisitor::visitArgList(VParser::ArgListContext *ctx) {
    vector<VConstraintExpr*> args;
    if (ctx->constraint()) {
      args.push_back(visitConstraint(ctx->constraint()));
      if (ctx->argList()) {
        VArgList *rest = visitArgList(ctx->argList());
        args.insert(args.end(), rest->args.begin(), rest->args.end());
      }
    }

    return new VArgList(args);
  }

  VConstraintExpr* VASTVisitor::visitArithExpr(VParser::ArithExprContext *ctx) {
    if (ctx->varOrNum()) {
      return visitVarOrNum(ctx->varOrNum());
    }

    if (ctx->arithExpr().size() > 0) {
      VConstraintExpr* a1 = visitArithExpr(ctx->arithExpr()[0]);
      if (ctx->arithExpr().size() == 2) {
        VConstraintExpr* a2 = visitArithExpr(ctx->arithExpr()[1]);
        string op_str;
        if (ctx->A1_BIN()) {
          op_str = ctx->A1_BIN()->getText();
        } else if (ctx->A2_BIN()) {
          op_str = ctx->A2_BIN()->getText();
        }
        VBinOp *op = new VBinOp(op_str);
        return new VBinExpr(a1, a2, op);
      }

      return a1;
    }

    return nullptr;
  }
}
