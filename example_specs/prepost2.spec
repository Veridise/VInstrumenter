Pre: started(ERC20.totalSupply(), this.totalSupply >= 0 && this.totalSupply < 256)
Post: finished(ERC20.totalSupply(), return == this.totalSupply)
