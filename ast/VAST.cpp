#include "VAST.h"

using namespace std;

namespace vast {
  VConstraint::VConstraint() {

  }
  string VConstraint::toJson() {
    return "";
  }

  VBehavioralSpec::VBehavioralSpec(VVarDecl var_decs, VConstraint pre, VConstraint post) {

  }

  string VBehavioralSpec::toJson() {
    return "";
  }

  VTestSpec::VTestSpec(VVarDecl var_decs, vector<VConstraint> init, vector<VConstraint> spec) {

  }
  string VTestSpec::toJson() {
    return "";
  }

  VTempSpec::VTempSpec(VVarDecl var_decs, VConstraint fairness, VConstraint spec) {

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

  VBinConstraint::VBinConstraint(VConstraint lhs, VConstraint RHS, VBinOp op) {

  }
  string VBinConstraint::toJson() {
    return "";
  }

  VBinOp::VBinOp(string op) {

  }
  string VBinOp::toJson() {
    return "";
  }

  VUnConstraint::VUnConstraint(VConstraint con, VUnOp op) {

  }
  string VUnConstraint::toJson() {
    return "";
  }

  VUnOp::VUnOp(string op) {

  }
  string VUnOp::toJson() {
    return "";
  }

  VExpr::VExpr() {

  }
  string VExpr::toJson() {
    return "";
  }

  VExecutedStatement::VExecutedStatement(VFunctionID fun, VExpr con) {

  }
  string VExecutedStatement::toJson() {
    return "";
  }

  VFinishedStatement::VFinishedStatement(VFunctionID fun, VExpr con) {

  }
  string VFinishedStatement::toJson() {
    return "";
  }

  VStartedStatement::VStartedStatement(VFunctionID fun, VExpr con) {

  }
  string VStartedStatement::toJson() {
    return "";
  }

  VRevertedStatement::VRevertedStatement(VFunctionID fun, VExpr con) {

  }
  string VRevertedStatement::toJson() {
    return "";
  }

  VWillSucceedStatement::VWillSucceedStatement(VFunctionID fun, VExpr con) {

  }
  string VWillSucceedStatement::toJson() {
    return "";
  }

  VFunctionID::VFunctionID(string name, VArgList args) {

  }

  string VFunctionID::toJson() {
    return "";
  }

  VArgList::VArgList(vector<VExpr> args) {

  }
  string VArgList::toJson() {
    return "";
  }

  VBinExpr::VBinExpr(VExpr lhs, VExpr RHS, VBinOp op) {

  }
  string VBinExpr::toJson() {
    return "";
  }

  VUnExpr::VUnExpr(VExpr expr, VUnOp op) {

  }
  string VUnExpr::toJson() {
    return "";
  }

  VVarExpr::VVarExpr(VVar var) {

  }
  string VVarExpr::toJson() {
    return "";
  }

  VFieldAccessExpr::VFieldAccessExpr(VExpr expr, string field) {

  }
  string VFieldAccessExpr::toJson() {
    return "";
  }

  VArrAccessExpr::VArrAccessExpr(VExpr arr, VExpr idx) {

  }
  string VArrAccessExpr::toJson() {
    return "";
  }

  VFuncCallExpr::VFuncCallExpr(string func, VArgList args) {

  }
  string VFuncCallExpr::toJson() {
    return "";
  }

  VFSumExpr::VFSumExpr(VFunctionID func, VConstraint con) {

  }
  string VFSumExpr::toJson() {
    return "";
  }

}
