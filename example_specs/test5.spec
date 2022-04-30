Vars: SideEntranceLenderPool lender, Attacker attacker
Init: finished(SideEntranceLenderPool, lender = this && msg.value = 1000) ;
finished(Attacker(lender), attacker = this)
Spec: finished(attacker.attack, address(this).balance = 1000 && address(lender).balance = 0)
