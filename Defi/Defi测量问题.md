###  DeFi中研究点

- DEX的算法
  - 方法介绍
    - 订单薄的方法。
    - 线上自动做市方法。
    - 线下撮合，线上交易的方法。
  - 方法对比
    - 各种方法的对流动性池大小的敏感性(滑点大小问题)。
    - 无常损失。
    - 效率、安全。
    - swap失败的比例对比，交易失败的情况有哪些？
- DEX中的套利
  - 套利空间是如何产生的？交易所中的swap、Oracle错误报价、套利的机会多吗？
  - 套利对于区块链的影响是什么？
    - 对套利进行分析，平均每个区块中套利交易的次数是多少？每次套利所得是多少？
    - 套利对区块链安全有什么影响？对矿工的行为的影响？
    - 对Liquid Provider造成了什么影响？是否会打击Liquid Provider的积极性？
    - 是不是造成Gas 费用增加和交易拥堵？
  - 空手套白狼-Flash Loan
    - Flash Loan对Defi生态带来的正面、负面影响。
    - 警惕大的矿池与人合谋进行套利。
- DeFi中的预言机
  - 预言机架构分类
    - 中心化式预言机
    - 去中心化的预言机
  - 预言机的安全性是如何保证的？
  - 预言机的安全性对整个DEX的影响。
- 整个Defi生态中的DApp对区块链安全带来的挑战是什么？



### DeFi的兴起对整个区块链生态引发的安全和技术挑战

- DEX

  - 方法介绍
    - 订单薄的方法。
    - 线上自动做市方法。
    - 线下撮合，线上交易的方法。
    
  - 方法对比
    - 各种方法的对流动性池大小的敏感性(滑点大小问题)。
    - 无常损失。
    - 效率、安全。
    - swap失败的比例对比，交易失败的情况有哪些？
    
  - DEX中的套利

    - 如何爬取套利交易？

      - 套利人: 0xD0648A380e26b85A378f0e48c9a5B3d8C5Aa19D4
      - 套利合约: 0x045fcf7f59765a56937609f72adec7fe6926407e
      - 信息来源: https://explore.duneanalytics.com/queries/13977/source 
      - Dune套利地址： https://explore.duneanalytics.com/queries/11284/source#22383

    - 套利空间是如何产生的？交易所中的swap、Oracle错误报价、套利的机会多吗？

    - 套利对于区块链的影响是什么？
      - 对套利进行分析，平均每个区块中套利交易的次数是多少？每次套利所得是多少？
      - 套利对区块链安全有什么影响？对矿工的行为的影响？
      - 对Liquid Provider造成了什么影响？是否会打击Liquid Provider的积极性？
      - 是不是造成Gas 费用增加和交易拥堵？

      - 警惕大的矿池与人合谋进行套利。

  - DEX中的骗局

    - 具有后门漏洞的ERC20代币
      - [我买了百倍币，却卖不出去](https://www.chainnews.com/articles/413317900427.htm)
      - 具有后门的ERC20代币
    - 缺乏监管
      - [DeFi骗局频发，翡翠、YFIII为什么可以骗到钱](https://www.zilian8.com/416698.html)
    - 智能合约漏洞导致财产损失
      - DeFi中各种攻击事件
      - Flash Loan的推波助澜
        - Flash Loan对Defi生态带来的正面、负面影响。
        - Flash Loan降低了攻击成本，对智能合约安全带来了更大的挑战。

- 智能合约衍生品

  - 多个合约之间的复杂调用，增加了被攻击的风险。

- Oracle

  - 预言机架构分类
    - 中心化式预言机
    - 去中心化的预言机
  - 预言机的安全性是如何保证的？
  - 预言机的安全性对整个DEX的影响。

- DeFi中的骗局

  - 利用代码漏洞制造的骗局

    - [项目UniCats 在合约嵌入恶意函式，诓走「20万美元UNI」](https://www.blocktempo.com/vicious-defi-project-unicats-set-malicious-code-on-smart-contract/)
    - [Uniswap 项目漏洞教程新骗局](https://www.anquanke.com/post/id/216188)
    - [不断扩张的骗局，玷污了DeFi收益耕种市场](https://www.beekuaibao.com/article/767771852414103552)
    - [从这轮DeFi起落中，我们学到了什么？](https://www.sohu.com/a/428068742_100217347)
    
  - 监管缺失造成的骗局

    

### Defi最新的论文

- [2020年SP会议- Flash Boys 2.0 Frontrunning in Decentralized Exchanges, Miner Extractable Value, and Consensus Instability](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=9152675)

  - 发现以太坊中多个套利机器人对同一笔套利交易多次提高Gas费用竞争。
  - 用博弈论分析了套利机器人的策略。
  - 指出套利这种机制的存在会影响矿工的行为，进而威胁到区块链的安全。

- [Arxiv-2020-03月上传-Attacking the Defi Ecosystem with Flash Loans for Fun and Profit](https://arxiv.org/pdf/2003.03810.pdf)

  - 探究闪电贷对整个Defi生态的影响。
  - 分析了已有的闪电贷攻击，找出闪电贷攻击的关键参数。

- [Arxiv-2020年-05月-A First Look into Defi Oracles](https://arxiv.org/pdf/2005.04377.pdf)

  - 分析目前使用的预言机的设计机制。
  - 系统性的分析了MakerDAO、Compound、AmpleForth和Synthetix上的预言机的优劣。
  - 使用交易图测量预言机的健壮性。

- [Arxiv-2020年10月23日上传-Towards Understanding Flash Loan and Its Applications in DeFi Ecosystem](https://arxiv.org/pdf/2010.12252.pdf)

  - 作者如下：
  - <img src="./image/image-20201117162948904.png" alt="image-20201117162948904" style="zoom:50%;" />
  - 该文主要贡献是设计了一个工具用于检测区块链网络中的闪电贷交易。

  ### Flash Loan的相关资料

  - [Value DeFi遭攻击始末，闪电贷这次又带走了700万美元](https://www.8btc.com/article/669039)
  - [Balancer 24小时内再遭闪电贷攻击](https://www.bitpush.news/articles/852985)
  - [The DeFi ‘Flash Loan’ Attack That Changed Everything](https://www.coindesk.com/the-defi-flash-loan-attack-that-changed-everything)
  - [Flash-loan attacks cause $34 million loss, but can they be stopped?](https://www.okex.com/academy/en/flash-loan-attacks-cause-34-million-loss-but-can-they-be-stopped-defi-digest)
  - [Our thoughts on the recent DeFi “Flashloan” attack](https://medium.com/iosg-ventures/our-thoughts-on-the-recent-defi-flashloan-attack-afe856b0a849)

### Uniswap V2中留有后门的代币有哪些？



- **TorontoCoin (TRTC)**
  - 地址：https://cn.etherscan.com/address/0xde693849626e66fe68a7a2b23ea731d7d87db886#code
  - 282行后门
- **Keep4rV1 (KPR4)**
  - 地址：https://cn.etherscan.com/address/0xb9675d55879d6cebd857ffb16303ced4b694e1e5#code
  - 231行后门
- **SKODAswap (SKODA)**
  - https://cn.etherscan.com/address/0xee5b50cc2a46ecc26c84a430fd0deff841042ceb#code
  - 231行后门



