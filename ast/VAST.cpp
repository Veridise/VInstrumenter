#include "VAST.h"

using json = nlohmann::json;
using namespace std;

namespace vast {
  VStatementExpr::VStatementExpr() {
    // Placeholder only
  }
  json VStatementExpr::toJson() {
    return "";
  }

  VBehavioralSpec::VBehavioralSpec(VVarDeclList *_var_decs, VStatementExpr *_pre, VStatementExpr *_post) {
    var_decs = _var_decs;
    pre = _pre;
    post = _post;
  }
  json VBehavioralSpec::toJson() {
    json varsJson = {};
    if (var_decs != nullptr) varsJson = var_decs->toJson();
    json preJson = {};
    if (pre != nullptr) preJson = pre->toJson();
    json postJson = post->toJson();
    json total = {
      {"VBehavioralSpec", {
          {"var_decs", varsJson}, {"pre", preJson}, {"post", postJson}
        }}
    };
    return total;
  }

  VTestSpec::VTestSpec(VVarDeclList *_var_decs, VStatementExpr *_init, VStatementExpr *_spec) {
    var_decs = _var_decs;
    init = _init;
    spec = _spec;
  }
  json VTestSpec::toJson() {
    json varsJson = {};
    if (var_decs != nullptr) varsJson = var_decs->toJson();
    json initJson = {};
    if (init != nullptr) initJson = init->toJson();
    json specJson = spec->toJson();
    json total = {
      {"VTestSpec", {
          {"var_decs", varsJson}, {"init", initJson}, {"spec", specJson}
        }}
    };
    return total;
  }

  VTempSpec::VTempSpec(VVarDeclList *_var_decs, VStatementExpr *_fairness, VStatementExpr *_spec) {
    var_decs = _var_decs;
    fairness = _fairness;
    spec = _spec;
  }
  json VTempSpec::toJson() {
    json varsJson = {};
    if (var_decs != nullptr) varsJson = var_decs->toJson();
    json fairnessJson = {};
    if (fairness != nullptr) fairnessJson = fairness->toJson();
    json specJson = spec->toJson();
    json total = {
      {"VTempSpec", {
          {"var_decs", varsJson}, {"fairness", fairnessJson}, {"spec", specJson}
        }}
    };
    return total;
  }

  VInvSpec::VInvSpec(VVarDeclList *_var_decs, VStatementExpr *_inv) {
    var_decs = _var_decs;
    inv = _inv;
  }
  json VInvSpec::toJson() {
    json varsJson = {};
    if (var_decs != nullptr) varsJson = var_decs->toJson();
    json invJson = inv->toJson();
    json total = {
      {"VInvSpec", {
          {"var_decs", varsJson}, {"inv", invJson}
        }}
    };
    return total;
  }

  VVarDeclList::VVarDeclList(vector<VVarDecl*> _var_decs) {
    var_decs = _var_decs;
  }
  json VVarDeclList::toJson() {
    vector<json> varDecsJson;
    for (VVarDecl* v : var_decs) {
      varDecsJson.push_back(v->toJson());
    }
    json declJson = {
      {"VVarDeclList", {
          {"var_decs", varDecsJson}
        }}
    };
    return declJson;
  }

  VVarDecl::VVarDecl(VType* _typ, VID* _var) {
    typ = _typ;
    var = _var;
  }
  json VVarDecl::toJson() {
    json declJson = {
      {"VVarDecl", {
          {"typ", typ->toJson()},
          {"var", var->toJson()}
        }}
    };
    return declJson;
  }

  VID::VID(string _name) {
    name = _name;
  }
  json VID::toJson() {
    json vidJson = {
      {"VID", {{"name", name}}}
    };
    return vidJson;
  }

  VType::VType(string _name, bool _is_arr) {
    name = _name;
    is_arr = _is_arr;
  }
  json VType::toJson() {
    string typ_str = name;
    if (is_arr) typ_str = name + "[]";
    json vtypJson = {
      {"VType", {{"name", typ_str}}}
    };
    return vtypJson;
  }

  VBinStatementExpr::VBinStatementExpr(VStatementExpr *_lhs, VStatementExpr *_rhs, VBinOp *_op) {
    lhs = _lhs;
    rhs = _rhs;
    op = _op;
  }
  json VBinStatementExpr::toJson() {
    json lhsJson = lhs->toJson();
    json rhsJson = rhs->toJson();
    json opJson = op->toJson();
    json vBinStmtExprJson = {
      {"VBinStatementExpr", {
          {"lhs", lhsJson}, {"rhs", rhsJson}, {"op", opJson}
        }}
    };
    return vBinStmtExprJson;
  }

  VBinOp::VBinOp(string _op) {
    op = _op;
  }
  json VBinOp::toJson() {
    json vBinOpJson = {{"VBinOp", {{"op", op}}}};
    return vBinOpJson;
  }

  VUnStatementExpr::VUnStatementExpr(VStatementExpr *_con, VUnOp *_op) {
    con = _con;
    op = _op;
  }
  json VUnStatementExpr::toJson() {
    json exprJson = con->toJson();
    json opJson = op->toJson();
    json vUnStmtExprJson = {
      {"VUnStatementExpr", {
          {"expr", exprJson}, {"op", opJson}
        }}
    };
    return vUnStmtExprJson;
  }

  VUnOp::VUnOp(string _op) {
    op = _op;
  }
  json VUnOp::toJson() {
    json vUnOpJson = {{"VUnOp", {{"op", op}}}};
    return vUnOpJson;
  }

  VConstraintExpr::VConstraintExpr() {
    // Placeholder only
  }
  json VConstraintExpr::toJson() {
    return "";
  }

  VExecutedStatement::VExecutedStatement(VFunctionID *_fun, VConstraintExpr *_con) {
    fun = _fun;
    con = _con;
  }
  json VExecutedStatement::toJson() {
    json funJson = fun->toJson();
    json conJson = {};
    if (con != nullptr) conJson = con->toJson();
    json vExecutedStmtJson = {
      {"VExecutedStatementExpr", {
          {"fun", funJson}, {"con", conJson}
        }}
    };
    return vExecutedStmtJson;
  }

  VFinishedStatement::VFinishedStatement(VFunctionID *_fun, VConstraintExpr *_con) {
    fun = _fun;
    con = _con;
  }
  json VFinishedStatement::toJson() {
    json funJson = fun->toJson();
    json conJson = {};
    if (con != nullptr) conJson = con->toJson();
    json vFinishedStmtJson = {
      {"VFinishedStatementExpr", {
          {"fun", funJson}, {"con", conJson}
        }}
    };
    return vFinishedStmtJson;
  }

  VStartedStatement::VStartedStatement(VFunctionID *_fun, VConstraintExpr *_con) {
    fun = _fun;
    con = _con;
  }
  json VStartedStatement::toJson() {
    json funJson = fun->toJson();
    json conJson = {};
    if (con != nullptr) conJson = con->toJson();
    json vStartedStmtJson = {
      {"VStartedStatementExpr", {
          {"fun", funJson}, {"con", conJson}
        }}
    };
    return vStartedStmtJson;
  }

  VRevertedStatement::VRevertedStatement(VFunctionID *_fun, VConstraintExpr *_con) {
    fun = _fun;
    con = _con;
  }
  json VRevertedStatement::toJson() {
    json funJson = fun->toJson();
    json conJson = {};
    if (con != nullptr) conJson = con->toJson();
    json vRevertedStmtJson = {
      {"VRevertedStatementExpr", {
          {"fun", funJson}, {"con", conJson}
        }}
    };
    return vRevertedStmtJson;
  }

  VWillSucceedStatement::VWillSucceedStatement(VFunctionID *_fun, VConstraintExpr *_con) {
    fun = _fun;
    con = _con;
  }
  json VWillSucceedStatement::toJson() {
    json funJson = fun->toJson();
    json conJson = {};
    if (con != nullptr) conJson = con->toJson();
    json vWillSucceedStmtJson = {
      {"VWillSucceedStatementExpr", {
          {"fun", funJson}, {"con", conJson}
        }}
    };
    return vWillSucceedStmtJson;
  }

  VFunctionID::VFunctionID(VConstraintExpr *_func, VArgList *_args) {
    func = _func;
    args = _args;
  }

  json VFunctionID::toJson() {
    json funcJson = func->toJson();
    json argsJson = {};
    if (args != nullptr) argsJson = args->toJson();
    json vFunctionIDJson = {
      {"VFunctionID", {
          {"func", funcJson}, {"args", argsJson}
        }}
    };
    return vFunctionIDJson;
  }

  VArgList::VArgList(vector<VConstraintExpr*> _args) {
    args = _args;
  }
  json VArgList::toJson() {
    vector<json> argsJson;
    for (VConstraintExpr* a : args) {
      argsJson.push_back(a->toJson());
    }
    json vArgListJson = {
      {"VArgList", {{"args", argsJson}}}
    };
    return vArgListJson;
  }

  VBinExpr::VBinExpr(VConstraintExpr *_lhs, VConstraintExpr *_rhs, VBinOp *_op) {
    lhs = _lhs;
    rhs = _rhs;
    op = _op;
  }
  json VBinExpr::toJson() {
    json lhsJson = lhs->toJson();
    json rhsJson = rhs->toJson();
    json opJson = op->toJson();
    json vBinExprJson = {
      {"VBinExpr", {
          {"lhs", lhsJson}, {"rhs", rhsJson}, {"op", opJson}
        }}
    };
    return vBinExprJson;
  }

  VUnExpr::VUnExpr(VConstraintExpr *_expr, VUnOp *_op) {
    expr = _expr;
    op = _op;
  }
  json VUnExpr::toJson() {
    json exprJson = expr->toJson();
    json opJson = op->toJson();
    json vUnExprJson = {
      {"VUnExpr", {
          {"expr", exprJson}, {"op", opJson}
        }}
    };
    return vUnExprJson;
  }

  VVarExpr::VVarExpr(VID *_var) {
    var = _var;
  }
  json VVarExpr::toJson() {
    json varJson = var->toJson();
    json vVarExprJson = {
      {"VVarExpr", {{"var", varJson}}}
    };
    return vVarExprJson;
  }

  VConstExpr::VConstExpr(string _val) {
    val = _val;
  }
  json VConstExpr::toJson() {
    return val;
  }

  VFieldAccessExpr::VFieldAccessExpr(VConstraintExpr *_expr, VID *_field) {
    expr = _expr;
    field = _field;
  }
  json VFieldAccessExpr::toJson() {
    json exprJson = expr->toJson();
    json fieldJson = field->toJson();
    json vFieldAccessExprJson = {
      {"VFieldAccessExpr", {
          {"expr", exprJson}, {"field", fieldJson}
        }}
    };
    return vFieldAccessExprJson;
  }

  VArrAccessExpr::VArrAccessExpr(VConstraintExpr *_arr, VConstraintExpr *_idx) {
    arr = _arr;
    idx = _idx;
  }
  json VArrAccessExpr::toJson() {
    json arrJson = arr->toJson();
    json idxJson = idx->toJson();
    json vArrAccessExprJson = {
      {"VArrAccessExpr", {
          {"arr", arrJson}, {"idx", idxJson}
        }}
    };
    return vArrAccessExprJson;
  }

  VFuncCallExpr::VFuncCallExpr(VConstraintExpr *_func, VArgList *_args) {
    func = _func;
    args = _args;
  }
  json VFuncCallExpr::toJson() {
    json funcJson = func->toJson();
    json argsJson = args->toJson();
    json vFuncCallExprJson = {
      {"VFuncCallExpr", {
          {"func", funcJson}, {"args", argsJson}
        }}
    };
    return vFuncCallExprJson;
  }

  VFSumExpr::VFSumExpr(VFunctionID *_func, VConstraintExpr* _arg, VConstraintExpr *_con) {
    func = _func;
    arg = _arg;
    con = _con;
  }
  json VFSumExpr::toJson() {
    json funcJson = func->toJson();
    json argJson = arg->toJson();
    json conJson = con->toJson();
    json vFSumExprJson = {
      {"VFSumExpr", {
          {"func", funcJson}, {"arg", argJson}, {"con", conJson}
        }}
    };
    return vFSumExprJson;
  }

}
