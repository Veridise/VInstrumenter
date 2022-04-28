#ifndef VINSTRUMENTER_VAST_H
#define VINSTRUMENTER_VAST_H

#include <string>
#include <vector>

using namespace std;

namespace vast {
  class VAST {
  public:
    virtual ~VAST() = default;
    virtual string toJson() = 0;
  };

  class VStatementExpr : public VAST {
  public:
    VStatementExpr();
    string toJson() override;
  };

  class VID : public VAST {
  public:
    VID(string name);
    string toJson() override;
  };

  class VType : public VAST {
  public:
    VType(string name, bool is_arr);
    string toJson() override;
  };

  class VVarDeclList : public VAST {
  public:
    VVarDeclList(vector<VType*> typs, vector<VID*> vars);
    string toJson() override;
    vector<VType*> typs;
    vector<VID*> vars;
  };

  class VBehavioralSpec : public VAST {
  public:
    VBehavioralSpec(VVarDeclList *var_decs, VStatementExpr *pre, VStatementExpr *post);
    string toJson() override;
  };

  class VTestSpec : public VAST {
  public:
    VTestSpec(VVarDeclList *var_decs, vector<VStatementExpr*> init, vector<VStatementExpr*> spec);
    string toJson() override;
  };

  class VTempSpec : public VAST {
  public:
    VTempSpec(VVarDeclList *var_decs, VStatementExpr *fairness, VStatementExpr *spec);
    string toJson() override;
  };

  class VBinOp : public VAST {
  public:
    VBinOp(string op);
    string toJson() override;
  };

  class VBinStatementExpr : public VStatementExpr {
  public:
    VBinStatementExpr(VStatementExpr *lhs, VStatementExpr *RHS, VBinOp *op);
    string toJson() override;
  };

  class VUnOp : public VAST {
  public:
    VUnOp(string op);
    string toJson() override;
  };

  class VUnStatementExpr : public VStatementExpr {
  public:
    VUnStatementExpr(VStatementExpr *con, VUnOp *op);
    string toJson() override;
  };

  class VConstraintExpr : public VAST {
  public:
    VConstraintExpr();
    string toJson() override;
  };

  class VArgList : public VAST {
  public:
    VArgList(vector<VConstraintExpr*> args);
    string toJson() override;
    vector<VConstraintExpr*> args;
  };

  class VFunctionID : public VAST {
  public:
    VFunctionID(string name, VArgList *args);
    string toJson() override;
  };

  class VExecutedStatement : public VStatementExpr {
  public:
    VExecutedStatement(VFunctionID *fun, VConstraintExpr *con);
    string toJson() override;
  };

  class VFinishedStatement : public VStatementExpr {
  public:
    VFinishedStatement(VFunctionID *fun, VConstraintExpr *con);
    string toJson() override;
  };

  class VStartedStatement : public VStatementExpr {
  public:
    VStartedStatement(VFunctionID *fun, VConstraintExpr *con);
    string toJson() override;
  };

  class VRevertedStatement : public VStatementExpr {
  public:
    VRevertedStatement(VFunctionID *fun, VConstraintExpr *con);
    string toJson() override;
  };

  class VWillSucceedStatement : public VStatementExpr {
  public:
    VWillSucceedStatement(VFunctionID *fun, VConstraintExpr *con);
    string toJson() override;
  };

  class VBinExpr : public VConstraintExpr {
  public:
    VBinExpr(VConstraintExpr *lhs, VConstraintExpr *rhs, VBinOp *op);
    string toJson() override;
  };

  class VUnExpr : public VConstraintExpr {
  public:
    VUnExpr(VConstraintExpr *expr, VUnOp *op);
    string toJson() override;
  };

  class VVarExpr : public VConstraintExpr {
  public:
    VVarExpr(VID *var);
    string toJson() override;
  };

  class VConstExpr : public VConstraintExpr {
  public:
    VConstExpr(string val);
    string toJson() override;
  };

  class VFieldAccessExpr : public VConstraintExpr {
  public:
    VFieldAccessExpr(VConstraintExpr *expr, VID* field);
    string toJson() override;
  };

  class VArrAccessExpr : public VConstraintExpr {
  public:
    VArrAccessExpr(VConstraintExpr *arr, VConstraintExpr *idx);
    string toJson() override;
  };

  class VFuncCallExpr : public VConstraintExpr {
  public:
    VFuncCallExpr(string func, VArgList *args);
    string toJson() override;
  };

  class VFSumExpr : public VConstraintExpr {
  public:
    VFSumExpr(VFunctionID *func, VConstraintExpr* arg, VConstraintExpr *con);
    string toJson() override;
  };

}

#endif
