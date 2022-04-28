#include <string>
#include <vector>

using namespace std;

namespace vast {
  class VAST {
  public:
    virtual ~VAST() = default;
    virtual string toJson() = 0;
  };

  class VStatementExpr : VAST {
  public:
    VStatementExpr();
    string toJson() override;
  };

  class VVar : VAST {
  public:
    VVar(string name);
    string toJson() override;
  };

  class VType : VAST {
  public:
    VType(string name, bool is_arr);
    string toJson() override;
  };

  class VVarDecl : VAST {
  public:
    VVarDecl(vector<tuple<VType, VVar>> vars);
    string toJson() override;
  };

  class VBehavioralSpec : VAST {
  public:
    VBehavioralSpec(VVarDecl var_decs, VStatementExpr pre, VStatementExpr post);
    string toJson() override;
  };

  class VTestSpec : VAST {
  public:
    VTestSpec(VVarDecl var_decs, vector<VStatementExpr> init, vector<VStatementExpr> spec);
    string toJson() override;
  };

  class VTempSpec : VAST {
  public:
    VTempSpec(VVarDecl var_decs, VStatementExpr fairness, VStatementExpr spec);
    string toJson() override;
  };

  class VBinOp : VAST {
  public:
    VBinOp(string op);
    string toJson() override;
  };

  class VBinStatementExpr : VStatementExpr {
  public:
    VBinStatementExpr(VStatementExpr lhs, VStatementExpr RHS, VBinOp op);
    string toJson() override;
  };

  class VUnOp : VAST {
  public:
    VUnOp(string op);
    string toJson() override;
  };

  class VUnStatementExpr : VStatementExpr {
  public:
    VUnStatementExpr(VStatementExpr con, VUnOp op);
    string toJson() override;
  };

  class VStatement : VStatementExpr {
  public:
    virtual ~VStatement() = default;
  };

  class VConstraintExpr : VAST {
  public:
    VConstraintExpr();
    string toJson() override;
  };

  class VArgList : VAST {
  public:
    VArgList(vector<VConstraintExpr> args);
    string toJson() override;
  };

  class VFunctionID : VStatement {
  public:
    VFunctionID(string name, VArgList args);
    string toJson() override;
  };

  class VExecutedStatement : VStatement {
  public:
    VExecutedStatement(VFunctionID fun, VConstraintExpr con);
    string toJson() override;
  };

  class VFinishedStatement : VStatement {
  public:
    VFinishedStatement(VFunctionID fun, VConstraintExpr con);
    string toJson() override;
  };

  class VStartedStatement : VStatement {
  public:
    VStartedStatement(VFunctionID fun, VConstraintExpr con);
    string toJson() override;
  };

  class VRevertedStatement : VStatement {
  public:
    VRevertedStatement(VFunctionID fun, VConstraintExpr con);
    string toJson() override;
  };

  class VWillSucceedStatement : VStatement {
  public:
    VWillSucceedStatement(VFunctionID fun, VConstraintExpr con);
    string toJson() override;
  };

  class VBinExpr : VConstraintExpr {
  public:
    VBinExpr(VConstraintExpr lhs, VConstraintExpr RHS, VBinOp op);
    string toJson() override;
  };

  class VUnExpr : VConstraintExpr {
  public:
    VUnExpr(VConstraintExpr expr, VUnOp op);
    string toJson() override;
  };

  class VVarExpr : VConstraintExpr {
  public:
    VVarExpr(VVar var);
    string toJson() override;
  };

  class VFieldAccessExpr : VConstraintExpr {
  public:
    VFieldAccessExpr(VConstraintExpr expr, string field);
    string toJson() override;
  };

  class VArrAccessExpr : VConstraintExpr {
  public:
    VArrAccessExpr(VConstraintExpr arr, VConstraintExpr idx);
    string toJson() override;
  };

  class VFuncCallExpr : VConstraintExpr {
  public:
    VFuncCallExpr(string func, VArgList args);
    string toJson() override;
  };

  class VFSumExpr : VConstraintExpr {
  public:
    VFSumExpr(VFunctionID func, VConstraintExpr con);
    string toJson() override;
  };

}
