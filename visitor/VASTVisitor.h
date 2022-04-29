#ifndef VINSTRUMENTER_VASTVISITOR_H
#define VINSTRUMENTER_VASTVISITOR_H

#include <string>
#include "antlr4-runtime.h"
#include "../libs/VParserBaseVisitor.h"
#include "../libs/VParser.h"
#include "../ast/VAST.h"

using namespace std;
using namespace vast;

namespace vastvisitor {
  class VASTVisitor {
  public:
    VAST* visitSpec(VParser::SpecContext *ctx);
    VBehavioralSpec* visitBehavioralSpec(VParser::BehavioralSpecContext *ctx);
    VTestSpec* visitTestSpec(VParser::TestSpecContext *ctx);
    VTempSpec* visitTempSpec(VParser::TempSpecContext *ctx);
    VVarDeclList* visitVarsSection(VParser::VarsSectionContext *ctx);
    vector<VStatementExpr*>* visitInitSection(VParser::InitSectionContext *ctx);
    vector<VStatementExpr*>* visitSpecSection(VParser::SpecSectionContext *ctx);
    VStatementExpr* visitLtlFairnessSection(VParser::LtlFairnessSectionContext *ctx);
    VStatementExpr* visitLtlPropertySection(VParser::LtlPropertySectionContext *ctx);
    VStatementExpr* visitSmartltlAtom(VParser::SmartltlAtomContext *ctx);
    vector<VStatementExpr*>* visitSeqAtom(VParser::SeqAtomContext *ctx);
    VVarDeclList* visitDeclList(VParser::DeclListContext *ctx);
    VType* visitTyp(VParser::TypContext *ctx);
    VID* visitIdent(VParser::IdentContext *ctx);
    VStatementExpr* visitPostcondSection(VParser::PostcondSectionContext *ctx);
    VStatementExpr* visitPrecondSection(VParser::PrecondSectionContext *ctx);
    VStatementExpr* visitAtom(VParser::AtomContext *ctx);
    VFunctionID* visitAtomFn(VParser::AtomFnContext *ctx);
    VArgList* visitParams(VParser::ParamsContext *ctx);
    VConstraintExpr* visitConstraint(VParser::ConstraintContext *ctx);
    VConstraintExpr* visitBoolExpr(VParser::BoolExprContext *ctx);
    VConstraintExpr* visitVarOrNum(VParser::VarOrNumContext *ctx);
    VConstraintExpr* visitVarAccess(VParser::VarAccessContext *ctx);
    VConstraintExpr* visitFnCall(VParser::FnCallContext *ctx);
    VArgList* visitArgList(VParser::ArgListContext *ctx);
    VConstraintExpr* visitArithExpr(VParser::ArithExprContext *ctx);
  private:
  };
}

#endif
