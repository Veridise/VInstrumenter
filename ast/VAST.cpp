#include "VAST.h"

using json = nlohmann::json;
using namespace std;

namespace vast {
  VStatementExpr::VStatementExpr() {

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
    if (preJson != nullptr) preJson = pre->toJson();
    json postJson = post->toJson();
    json total = {
      {"VBehavioralSpec", {
          varsJson, preJson, postJson
        }}
    };
    return total;
  }

  VTestSpec::VTestSpec(VVarDeclList *_var_decs, vector<VStatementExpr*> _init, vector<VStatementExpr*> _spec) {
    var_decs = _var_decs;
    init = _init;
    spec = _spec;
  }
  json VTestSpec::toJson() {
    json varsJson = {};
    if (var_decs != nullptr) varsJson = var_decs->toJson();
    vector<json> initJson;
    for (VStatementExpr* s : init) {
      initJson.push_back(s->toJson());
    }
    vector<json> specJson;
    for (VStatementExpr* s : spec) {
      specJson.push_back(s->toJson());
    }
    json total = {
      {"VTestSpec", {
          varsJson, initJson, specJson
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
    if (fairnessJson != nullptr) fairnessJson = fairness->toJson();
    json specJson = spec->toJson();
    json total = {
      {"VTempSpec", {
          varsJson, fairnessJson, specJson
        }}
    };
    return total;
  }

  VVarDeclList::VVarDeclList(vector<VType*> _typs, vector<VID*> _vars) {
    typs = _typs;
    vars = _vars;
  }
  json VVarDeclList::toJson() {
    vector<json> typsJson;
    for (VType* t : typs) {
      typsJson.push_back(t->toJson());
    }
    vector<json> varsJson;
    for (VID* v : vars) {
      varsJson.push_back(v->toJson());
    }
    json declJson = {
      {"VVarDeclList", {
          {"typs", typsJson},
          {"vars", varsJson}
        }}
    };
    return declJson;
  }

  VID::VID(string _name) {
    name = _name;
  }
  json VID::toJson() {
    json vidJson = {
      {"VID", name}
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
      {"VType", typ_str}
    };
    return vtypJson;
  }

  VBinStatementExpr::VBinStatementExpr(VStatementExpr *lhs, VStatementExpr *RHS, VBinOp *op) {

  }
  json VBinStatementExpr::toJson() {
    return "";
  }

  VBinOp::VBinOp(string op) {

  }
  json VBinOp::toJson() {
    return "";
  }

  VUnStatementExpr::VUnStatementExpr(VStatementExpr *con, VUnOp *op) {

  }
  json VUnStatementExpr::toJson() {
    return "";
  }

  VUnOp::VUnOp(string op) {

  }
  json VUnOp::toJson() {
    return "";
  }

  VConstraintExpr::VConstraintExpr() {

  }
  json VConstraintExpr::toJson() {
    return "";
  }

  VExecutedStatement::VExecutedStatement(VFunctionID *fun, VConstraintExpr *con) {

  }
  json VExecutedStatement::toJson() {
    return "";
  }

  VFinishedStatement::VFinishedStatement(VFunctionID *fun, VConstraintExpr *con) {

  }
  json VFinishedStatement::toJson() {
    return "";
  }

  VStartedStatement::VStartedStatement(VFunctionID *fun, VConstraintExpr *con) {

  }
  json VStartedStatement::toJson() {
    return "";
  }

  VRevertedStatement::VRevertedStatement(VFunctionID *fun, VConstraintExpr *con) {

  }
  json VRevertedStatement::toJson() {
    return "";
  }

  VWillSucceedStatement::VWillSucceedStatement(VFunctionID *fun, VConstraintExpr *con) {

  }
  json VWillSucceedStatement::toJson() {
    return "";
  }

  VFunctionID::VFunctionID(string name, VArgList *args) {

  }

  json VFunctionID::toJson() {
    return "";
  }

  VArgList::VArgList(vector<VConstraintExpr*> args) {

  }
  json VArgList::toJson() {
    return "";
  }

  VBinExpr::VBinExpr(VConstraintExpr *lhs, VConstraintExpr *rhs, VBinOp *op) {

  }
  json VBinExpr::toJson() {
    return "";
  }

  VUnExpr::VUnExpr(VConstraintExpr *expr, VUnOp *op) {

  }
  json VUnExpr::toJson() {
    return "";
  }

  VVarExpr::VVarExpr(VID *var) {

  }
  json VVarExpr::toJson() {
    return "";
  }

  VConstExpr::VConstExpr(string val) {

  }
  json VConstExpr::toJson() {
    return "";
  }

  VFieldAccessExpr::VFieldAccessExpr(VConstraintExpr *expr, VID *field) {

  }
  json VFieldAccessExpr::toJson() {
    return "";
  }

  VArrAccessExpr::VArrAccessExpr(VConstraintExpr *arr, VConstraintExpr *idx) {

  }
  json VArrAccessExpr::toJson() {
    return "";
  }

  VFuncCallExpr::VFuncCallExpr(string func, VArgList *args) {

  }
  json VFuncCallExpr::toJson() {
    return "";
  }

  VFSumExpr::VFSumExpr(VFunctionID *func, VConstraintExpr* arg, VConstraintExpr *con) {

  }
  json VFSumExpr::toJson() {
    return "";
  }

}
