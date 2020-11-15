# DEX 

## Top10 DEX的特点

### 1. Uniswap v2

white paper: https://uniswap.org/whitepaper.pdf

特点：第一个使用AMM算法做市的DEX，具有先发优势，开发团队并没有从中赚取收益。

做市算法: $XY=C$。

收益模式：通过代币之间的交易赚取交易费，交易费全部归LP所有。

### 2. Curve.fi

white paper: https://www.curve.fi/stableswap-paper.pdf

特点: 只支持**稳定币**兑换的交易所。

做市算法： $An^n\sum{x_i}+D = ADn^n+\frac{D^{n+1}}{n^n\prod{x_i}}$， 其中A = 85，是实验所得参数。D是所有代币资产总和，n是代币种类数，$x_i$是第i中代币的数量。

当稳定币之间差价非常小的时候，做市算法可以是恒定和的形式，够保证非常小的滑点；当稳定币之间差价变大时，该做市算法能够转化为恒定乘积的形式。

收益模式: 通过稳定币之间的交易赚取交易费，交易费用大部分归LP所有，一小部分归开发团队。

### 3. Balancer

white paper: https://balancer.finance/whitepaper/

特点: 支持多种代币交易的交易所，最多支持8中代币的交易。Uniswap中每次提供两种代币，每种代币50%的权重，而在BalancerLP可以同时拿出多种代币提供流动性，并且为每一种代币提供相应的分配权重。

做市算法：改进Uniswap 的AMM算法，使用 $V = \prod{B_t^{W^t}}$，$B_t$是每种代币的数量，$W_t$是代币的权重，其中$\sum{W_t}=1$。

### 4. Kyber

white paper: 无

特点: 订单薄形式的DEX，帮助用户从众多订单薄中找到最优的兑换率并完成交易。具体来讲，代币兑换者发送请求后，Kyber协议的智能合约并不是随机挑选储备库完成代币兑换，而是从不同的储备库中进行查询，比较得出最好的兑换率之后才执行交易。Kyber也计划支持跨链代币兑换，计划采用很多项目使用的中继的方式，通过两个区块链的区块头进行双向中继，一个区块链的区块头持续提交到另外一个区块链的智能合约。

### 5. Bancor

white paper: https://cryptorating.eu/whitepapers/Bancor/bancor_protocol_whitepaper_en.pdf

特点: 支持代币交易的DEX，致力于减少LP的无常损失，同时支持LP提供单一币种。与_Chainlink 预言机的关键整合。当一个代币的价格变化时，预言机（oracle）会向 Bancor AMMs 发送一条更新。AMMs 会进行相应调整，在套利者从差价中获利之前锁定新的价格。

### 6. Loopring

white paper: https://github.com/Loopring/protocols/blob/master/packages/loopring_v3/DESIGN.md



### 7. 0x Staking

white paper: 

### 8. DiversFi

white paper:

### 9. DDEX

white paper:

### 10. airswap

white paper: https://www.airswap.io/pdfs/SwapWhitepaper.pdf

使用线下中心化的撮合模式+线上去中心化交易的DEX。交易双方可以直接点对点沟通。为了协助沟通中的定价过程，定价机制提供了从多个数据源生成的定价建议。待交易双方沟通并确定价格后，一方下订单，另一方将该订单提交到智能合约进行链上结算。