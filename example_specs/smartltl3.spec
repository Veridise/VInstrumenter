Variables: address a
LTLFairness: [](<>(started(Auction.Withdraw, msg.sender == a))) && [](!started(Auction.Withdraw, msg.sender == a && a == this.highestBidder)) && [](!reverted(send(from, to, amt), to == a)) && [](!started(Auction.AuctionEnd, this.beneficiary == a))
LTLProperty: [](finished(Auction.Bid, msg.sender == a && msg.value != 0) ==> <>(finished(send(from, to, amt), to == a))) && [](!started(send(from, to, amt), to == a && amt != fsum(Auction.Bid, 2, msg.sender == a) - fsum(send(from, to, amt), 2, to == a)))
