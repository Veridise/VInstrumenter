Vars: ERC20 erc20, UnstoppableLender lender, ReceiverUnstoppable user, Attacker attacker
Init: finished(ERC20(2000000), erc20==this) ;
finished(UnstoppableLender(erc20), lender == this) ;
finished(ReceiverUnstoppable(lender), user == this) ;
finished(Attacker(lender, user), attacker == this) ;
finished(erc20.approve(lender, 1000000)) ;
finished(lender.depositTokens(1000000)) ;
finished(erc20.transfer(attacker, 100))
Spec: finished(attacker.attack) && reverted(user.executeFlashLoan(10))
