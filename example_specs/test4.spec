Vars: ERC20 token, TrustedLenderPool lender, Attacker attacker
Init: finished(ERC20(2000000), token = this) ;
finished(TrustedLenderPool(token), lender = this) ;
finished(Attacker(lender), attacker = this) ;
finished(token.transfer(lender, 1000000))
Spec: finished(attacker.attack, token.balanceof(this) = 1000000 && token.balanceof(lender) = 0)
