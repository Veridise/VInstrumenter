Vars: FlashLoanReceiver user, NaiveReceiverLenderPool lender, Attacker attacker
Init:
finished(NaiveReceiverLenderPool(), lender == this && msg.value == 1000) ;
finished(FlashLoanReceiver(lender), user == this && msg.value == 10) ;
finished(Attacker(user), attacher == this)
Spec: finished(attacker.attack, address(user).balance == 0)
