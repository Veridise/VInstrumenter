#include "VAST.h"

using namespace std;

namespace vast {
  VStatementExpr::VStatementExpr() {

  }
  string VStatementExpr::toJson() {
    return "";
  }

  VBehavioralSpec::VBehavioralSpec(VVarDecl var_decs, VStatementExpr pre, VStatementExpr post) {

  }

  string VBehavioralSpec::toJson() {
    return "";
  }

  VTestSpec::VTestSpec(VVarDecl var_decs, vector<VStatementExpr> init, vector<VStatementExpr> spec) {

  }
  string VTestSpec::toJson() {
    return "";
  }

  VTempSpec::VTempSpec(VVarDecl var_decs, VStatementExpr fairness, VStatementExpr spec) {

  }
  string VTempSpec::toJson() {
    return "";
  }

  VVarDecl::VVarDecl(vector<tuple<VType, VVar>> vars) {

  }
  string VVarDecl::toJson() {
    return "";
  }

  VVar::VVar(string name) {

  }
  string VVar::toJson() {
    return "";
  }

  VType::VType(string name, bool is_arr) {

  }
  string VType::toJson() {
    return "";
  }

  VBinStatementExpr::VBinStatementExpr(VStatementExpr lhs, VStatementExpr RHS, VBinOp op) {

  }
  string VBinStatementExpr::toJson() {
    return "";
  }

  VBinOp::VBinOp(string op) {

  }
  string VBinOp::toJson() {
    return "";
  }

  VUnStatementExpr::VUnStatementExpr(VStatementExpr con, VUnOp op) {

  }
  string VUnStatementExpr::toJson() {
    return "";
  }

  VUnOp::VUnOp(string op) {

  }
  string VUnOp::toJson() {
    return "";
  }

  VConstraintExpr::VConstraintExpr() {

  }
  string VConstraintExpr::toJson() {
    return "";
  }

  VExecutedStatement::VExecutedStatement(VFunctionID fun, VConstraintExpr con) {

  }
  string VExecutedStatement::toJson() {
    return "";
  }

  VFinishedStatement::VFinishedStatement(VFunctionID fun, VConstraintExpr con) {

  }
  string VFinishedStatement::toJson() {
    return "";
  }

  VStartedStatement::VStartedStatement(VFunctionID fun, VConstraintExpr con) {

  }
  string VStartedStatement::toJson() {
    return "";
  }

  VRevertedStatement::VRevertedStatement(VFunctionID fun, VConstraintExpr con) {

  }
  string VRevertedStatement::toJson() {
    return "";
  }

  VWillSucceedStatement::VWillSucceedStatement(VFunctionID fun, VConstraintExpr con) {

  }
  string VWillSucceedStatement::toJson() {
    return "";
  }

  VFunctionID::VFunctionID(string name, VArgList args) {

  }

  string VFunctionID::toJson() {
    return "";
  }

  VArgList::VArgList(vector<VConstraintExpr> args) {

  }
  string VArgList::toJson() {
    return "";
  }

  VBinExpr::VBinExpr(VConstraintExpr lhs, VConstraintExpr RHS, VBinOp op) {

  }
  string VBinExpr::toJson() {
    return "";
  }

  VUnExpr::VUnExpr(VConstraintExpr expr, VUnOp op) {

  }
  string VUnExpr::toJson() {
    return "";
  }

  VVarExpr::VVarExpr(VVar var) {

  }
  string VVarExpr::toJson() {
    return "";
  }

  VFieldAccessExpr::VFieldAccessExpr(VConstraintExpr expr, string field) {

  }
  string VFieldAccessExpr::toJson() {
    return "";
  }

  VArrAccessExpr::VArrAccessExpr(VConstraintExpr arr, VConstraintExpr idx) {

  }
  string VArrAccessExpr::toJson() {
    return "";
  }

  VFuncCallExpr::VFuncCallExpr(string func, VArgList args) {

  }
  string VFuncCallExpr::toJson() {
    return "";
  }

  VFSumExpr::VFSumExpr(VFunctionID func, VConstraintExpr con) {

  }
  string VFSumExpr::toJson() {
    return "";
  }

}