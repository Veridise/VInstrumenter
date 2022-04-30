invariant: finished(ERC20.transfer(to, amt), old(balanceOf(msg.sender)) >= amt ==> balanceOf(msg.sender) == old(balanceOf(msg.sender)) - amt && balanceOf(to) == old(blanceOf(to)) + amt)
