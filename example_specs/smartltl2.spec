Variables: address a
LTLProperty: [](!finished(*, this.pendingReturns[a] != fsum(Auction.Bid, 2, msg.sender == a) - fsum(send(from, to, amt), 2, to == a)))
