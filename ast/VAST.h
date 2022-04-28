#ifndef VINSTRUMENTER_VAST_H
#define VINSTRUMENTER_VAST_H

#include <string>
#include <vector>
#include <iostream>
#include "../libs/json.hpp"

using json = nlohmann::json;
using namespace std;

namespace vast {
  class VAST {
  public:
    virtual ~VAST() = default;
    virtual json toJson() = 0;
  };

  class VStatementExpr : public VAST {
  public:
    VStatementExpr();
    json toJson() override;
  };

  class VID : public VAST {
  public:
    VID(string _name);
    string name;
    json toJson() override;
  };

  class VType : public VAST {
  public:
    VType(string _name, bool _is_arr);
    string name;
    bool is_arr;
    json toJson() override;
  };

  class VVarDeclList : public VAST {
  public:
    VVarDeclList(vector<VType*> _typs, vector<VID*> _vars);
    json toJson() override;
    vector<VType*> typs;
    vector<VID*> vars;
  };

  class VBehavioralSpec : public VAST {
  public:
    VBehavioralSpec(VVarDeclList *_var_decs, VStatementExpr *_pre, VStatementExpr *_post);
    VVarDeclList *var_decs;
    VStatementExpr *pre;
    VStatementExpr *post;
    json toJson() override;
  };

  class VTestSpec : public VAST {
  public:
    VTestSpec(VVarDeclList *_var_decs, vector<VStatementExpr*> _init, vector<VStatementExpr*> _spec);
    VVarDeclList *var_decs;
    vector<VStatementExpr*> init;
    vector<VStatementExpr*> spec;
    json toJson() override;
  };

  class VTempSpec : public VAST {
  public:
    VTempSpec(VVarDeclList *_var_decs, VStatementExpr *_fairness, VStatementExpr *_spec);
    VVarDeclList *var_decs;
    VStatementExpr *fairness;
    VStatementExpr *spec;
    json toJson() override;
  };

  class VBinOp : public VAST {
  public:
    VBinOp(string op);
    json toJson() override;
  };

  class VBinStatementExpr : public VStatementExpr {
  public:
    VBinStatementExpr(VStatementExpr *lhs, VStatementExpr *RHS, VBinOp *op);
    json toJson() override;
  };

  class VUnOp : public VAST {
  public:
    VUnOp(string op);
    json toJson() override;
  };

  class VUnStatementExpr : public VStatementExpr {
  public:
    VUnStatementExpr(VStatementExpr *con, VUnOp *op);
    json toJson() override;
  };

  class VConstraintExpr : public VAST {
  public:
    VConstraintExpr();
    json toJson() override;
  };

  class VArgList : public VAST {
  public:
    VArgList(vector<VConstraintExpr*> args);
    json toJson() override;
    vector<VConstraintExpr*> args;
  };

  class VFunctionID : public VAST {
  public:
    VFunctionID(string name, VArgList *args);
    json toJson() override;
  };

  class VExecutedStatement : public VStatementExpr {
  public:
    VExecutedStatement(VFunctionID *fun, VConstraintExpr *con);
    json toJson() override;
  };

  class VFinishedStatement : public VStatementExpr {
  public:
    VFinishedStatement(VFunctionID *fun, VConstraintExpr *con);
    json toJson() override;
  };

  class VStartedStatement : public VStatementExpr {
  public:
    VStartedStatement(VFunctionID *fun, VConstraintExpr *con);
    json toJson() override;
  };

  class VRevertedStatement : public VStatementExpr {
  public:
    VRevertedStatement(VFunctionID *fun, VConstraintExpr *con);
    json toJson() override;
  };

  class VWillSucceedStatement : public VStatementExpr {
  public:
    VWillSucceedStatement(VFunctionID *fun, VConstraintExpr *con);
    json toJson() override;
  };

  class VBinExpr : public VConstraintExpr {
  public:
    VBinExpr(VConstraintExpr *lhs, VConstraintExpr *rhs, VBinOp *op);
    json toJson() override;
  };

  class VUnExpr : public VConstraintExpr {
  public:
    VUnExpr(VConstraintExpr *expr, VUnOp *op);
    json toJson() override;
  };

  class VVarExpr : public VConstraintExpr {
  public:
    VVarExpr(VID *var);
    json toJson() override;
  };

  class VConstExpr : public VConstraintExpr {
  public:
    VConstExpr(string val);
    json toJson() override;
  };

  class VFieldAccessExpr : public VConstraintExpr {
  public:
    VFieldAccessExpr(VConstraintExpr *expr, VID* field);
    json toJson() override;
  };

  class VArrAccessExpr : public VConstraintExpr {
  public:
    VArrAccessExpr(VConstraintExpr *arr, VConstraintExpr *idx);
    json toJson() override;
  };

  class VFuncCallExpr : public VConstraintExpr {
  public:
    VFuncCallExpr(string func, VArgList *args);
    json toJson() override;
  };

  class VFSumExpr : public VConstraintExpr {
  public:
    VFSumExpr(VFunctionID *func, VConstraintExpr* arg, VConstraintExpr *con);
    json toJson() override;
  };

}

#endif
