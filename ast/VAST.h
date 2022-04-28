#include <string>
#include <vector>

using namespace std;

namespace vast {
  class VAST {
  public:
    virtual ~VAST() = default;
    virtual string toJson() = 0;
  };

  class VConstraint : VAST {
  public:
    VConstraint();
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
    VBehavioralSpec(VVarDecl var_decs, VConstraint pre, VConstraint post);
    string toJson() override;
  };

  class VTestSpec : VAST {
  public:
    VTestSpec(VVarDecl var_decs, vector<VConstraint> init, vector<VConstraint> spec);
    string toJson() override;
  };

  class VTempSpec : VAST {
  public:
    VTempSpec(VVarDecl var_decs, VConstraint fairness, VConstraint spec);
    string toJson() override;
  };

  class VBinOp : VAST {
  public:
    VBinOp(string op);
    string toJson() override;
  };

  class VBinConstraint : VConstraint {
  public:
    VBinConstraint(VConstraint lhs, VConstraint RHS, VBinOp op);
    string toJson() override;
  };

  class VUnOp : VAST {
  public:
    VUnOp(string op);
    string toJson() override;
  };

  class VUnConstraint : VConstraint {
  public:
    VUnConstraint(VConstraint con, VUnOp op);
    string toJson() override;
  };

  class VStatement : VConstraint {
  public:
    virtual ~VStatement() = default;
  };

  class VExpr : VAST {
  public:
    VExpr();
    string toJson() override;
  };

  class VArgList : VAST {
  public:
    VArgList(vector<VExpr> args);
    string toJson() override;
  };

  class VFunctionID : VStatement {
  public:
    VFunctionID(string name, VArgList args);
    string toJson() override;
  };

  class VExecutedStatement : VStatement {
  public:
    VExecutedStatement(VFunctionID fun, VExpr con);
    string toJson() override;
  };

  class VFinishedStatement : VStatement {
  public:
    VFinishedStatement(VFunctionID fun, VExpr con);
    string toJson() override;
  };

  class VStartedStatement : VStatement {
  public:
    VStartedStatement(VFunctionID fun, VExpr con);
    string toJson() override;
  };

  class VRevertedStatement : VStatement {
  public:
    VRevertedStatement(VFunctionID fun, VExpr con);
    string toJson() override;
  };

  class VWillSucceedStatement : VStatement {
  public:
    VWillSucceedStatement(VFunctionID fun, VExpr con);
    string toJson() override;
  };

  class VBinExpr : VExpr {
  public:
    VBinExpr(VExpr lhs, VExpr RHS, VBinOp op);
    string toJson() override;
  };

  class VUnExpr : VExpr {
  public:
    VUnExpr(VExpr expr, VUnOp op);
    string toJson() override;
  };

  class VVarExpr : VExpr {
  public:
    VVarExpr(VVar var);
    string toJson() override;
  };

  class VFieldAccessExpr : VExpr {
  public:
    VFieldAccessExpr(VExpr expr, string field);
    string toJson() override;
  };

  class VArrAccessExpr : VExpr {
  public:
    VArrAccessExpr(VExpr arr, VExpr idx);
    string toJson() override;
  };

  class VFuncCallExpr : VExpr {
  public:
    VFuncCallExpr(string func, VArgList args);
    string toJson() override;
  };

  class VFSumExpr : VExpr {
  public:
    VFSumExpr(VFunctionID func, VConstraint con);
    string toJson() override;
  };

}
