# SDTE: A Secure Blockchain-based Data Trading Ecosystem  

## Contributions

- We introduce a secure data trading ecosystem and present a new blockchain-based data trading ecosystem(SDTE).
- Build a security model to analyze the data trading market, and describe a new set of trading protocols for the entire data trading market.

## SGX

- Protect data processing, the source data and the analysis results.

## blockchain

- To prevent single-point failure.
- Every transaction in SDTE is transparent.
- Facilitates the detection of any modification of transaction information.

## Detail

- Buyer deploys some data processing algorithm in the form of a smart contract on secure data trading platform(SDTP).  **Why do you use smart contract to deploy algorithm ?**
- The buyer identifies the data of interest, locates the prospective sellers and a number of trusted nodes to execute the data analysis contract through a broadcast contract (**buyer demand broadcast contract – BDBC**)  on SDTP.
  - The trusted nodes in SDTP have two Ethereum virtual machines (EVMs), where one EVM is protected by SGX and the other is a conventional EVM without SGX-protection.  
  - The data analysis contract will only be executed in the SGX-protected EVM on the trust nodes.
  - The traditional contract is executed on the conventional EVM of normal nodes and trusted nodes.  
- The buyer will then filter the sellers and the trusted nodes based on their information recorded in the **contract information storage contract (CISC)** and the speed of the complete SGX remote attestation that executes the smart contract.
  - Remote attestation：SGX生成一对公私钥(pk, sk)， 使用buyer的公钥加密sk, 再将pk和sk一起发送给buyer.
  - buyer收到信息后使用给自己的sk' 解密得到sk， 并将pk发送给DTMC，**如果buyer发送错误的pk怎么办？**
  - DTMC可以用该pk验证SGX对运行结果的签名，以确保运行数据没有被篡改。
- The buyer presents the key to encrypt the data analysis result to the selected trusted nodes enclave after the successful execution of the **SGX remote attestation**.  What's it?
  - Both buyers encryption key and sellers decryption key are one-time keys, which will be sealed using the SGX seal method for latter use.  
- The buyer pre-stores a sum of money on the management contract (data trading management contract, DTMC) and sets the payment amount for both seller and selected trusted nodes upon successful execution of the data analysis contract.          
- The seller and the selected nodes will check their reward and the contract by respectively calling DTMC and CISC. If the findings from calling DTMC / CISC align with their expectations, then the seller will send the encrypted raw data to the trusted nodes.
- The selected nodes will decrypt the sellers row data and execute the data analysis contract. **How to guarantee the seller‘s data will not leak to trust nodes ?**
- The buyer’s selected trust nodes will decrypt the sellers row data and then execute the analysis contract in SGX.  
- These trusted nodes will proceed to encrypt findings from the data analysis using the buyers key in the
  enclave.   
- The resultant information (hash, size and so on, but excluding the unencrypted results) will be sent to DTMC by the trusted nodes, in order to achieve a consensus on the blockchain.  
- DTMC will count the number of different calculation results, and the outcome with the largest number of identical results will be used as the final result.  
-  After that, DTMC will reward the seller and selected trusted nodes, according to the final outcome. 
-  Finally, the trusted nodes will send the encrypted data analysis result to the buyer.   
- The buyer retrieves the balance in DTMC and provides feedback for the seller to DTMC.  
- DTMC will provide the buyers comment, resultant information (hash, size and so on, but excluding the unencrypted results) to CISC that can be sent to future buyers.  





## 问题

**Remote attestation：** SGX建立私有连接的一种方式，只有Enclave和外部节点可以通信，通信内容直接进入Enclave，外部无法获取这些信息。

1. 为什么Algorithm要一定上传到智能合约中，其意义是什么？
   1. 猜测是为了SGX运算时容易实现计量定价和输出收费。
   2. 防止恶意的Algorithm无限循环，为了终止这种Algorithm，已有的EVM方便计价。
   3. 使用EVM本身的运行效率底下，不支持浮点数运算、难以调试等问题，增加了buyer的难度。
2. Trust node，到底trust它什么？ 其存在的意义是什么？
   1. trust node只是拥有SGX硬件的可信执行环境，其他方面并不可信。
3. 如果每个Trust都是恶意的，DTMC中仍然可以达成共识，buyer如何知道SGX正确运行了buyer的Algorithm？如何防止Trust node执行其他Algorithm？
   1. 假定SGX建立的remote attestation是可信的，且信息无法被外部解密，因为解密的私钥在SGX中而外部无法访问。
   2. Buyer从SGX处获取ID之后，将$ID, A_{contract}, A_{node}, A_{seller}, P_{node}, P_{seller}, IP_{seller}, T_{node}, T_{seller}, Pub_{enclave}$发送给DTMC合约中进行记录。
      1. ID: SGX为此次之行任务生成的唯一ID。
      2. $A_{contract}$是合约的地址(目前没有确认，本人猜测)。
      3. $A_{seller}$指定了节点的地址。
      4. $P_{seller}和T_{seller}$指定了seller的单位数据的价格和总价格上限。
      5. $P_{node}和T_{node}$指定了trust node对算法单位命令执行的价格和总价格上限。
      6. $Pub_{enclave}指SGX生成的私钥$。
   3. SGX中执行结果完毕后，对ID进行签名， DTMC最终进行使用$Pbu_{enclave}$对SGX的签名验证时，可以验证SGX执行的ID是否正确。**但是这里面问题是，没有保证ID与$A_{contract}$的一一对应关系，在这篇paper的方法中, SGX对于$A_{contract}$的获取只是单一的从与Seller的remote attestation过程中获取，更好的方式是应该另外与Buyer的remote attestation的连接过程中，Buyer向SGX发送$A_{contract}$, SGX收到Seller的$A_{contract}$时可以进行比对，如果无法匹配，则说明运行的结果不是Buyer指定的合约，可以直接结束运行**。
4. Seller如何将自己的私钥发送给SGX而不被trust node截获？
   1.  通过SGX的remote attestation实现。
   2. Trust Nodes 知道buyer指定的seller，根据IP地址判定是否进行remote attestation。
   3. Seller与SGX建立私有通道，随后将$ID, SK_{seller}, A_{contract}$发送给SGX，ID应该与SGX为Buyer生成的$ID$一致。 $SK_{seller}$是Seller为其数据加密的密钥， $A_{contract}$应该是需要执行的合约。
   4. 通过上述步骤完成私钥交换。
   5. **假定这个过程中私密通信的过程数据不会被获取，但是做到这一点很难，因此发送的$SK_{seller}$应该使用$Pub_{enclave}$加密才对，但是文章中没有这样做。**
   6. SGX获取$<ID, A_{contract}, SK_{seller}>$之后完成映射，并使用**seal method**加密后放置于SGX之外。
5. Buyer和SGX的remote attestation过程？
   1. Buyer制定分析算法合约和数据集需求，价格、节点数量等信息，发送给BDBC。与此同时，buyer也将自己的ip和指定的合约进行广播(第7页Step(1))。
   2. BDBC广播信息给Trust node， Trust node争向回复自己的ip和支持的算法,而Buyer会选择n个trust nodes作为trust nodes.
   3. Buyer与Trusted Nodes中的SGX进行同步，将自己的公钥$PK_{buyer}$发送给SGX， SGX用$PK_{buyer}$对运行结果加密。
   4. **SGX**节点同时生成一个ID，**ID与buyer指定的合约唯一对应**。然后生成一个公私钥对$(PK_{sgx}, SK_{sgx})$, 用$PK_{buyer}$加密$SK_{sgx}$, 将$ID, PK_{enclave}, encrypt(SK_{enclave}, PK_{buyer})$。
   5. Buyer之前的广播请求也会被Seller收到，Seller会向Buyer发送响应信息$IP_{seller}, A_{seller}$, 表示自己的IP地址和支持的算法。
   6. Buyer从CISC中筛选符合要求的Seller.
6. **如果在remote attestaton过程中trust node自己生成公私钥对而代替SGX生成，如何发现并且验证这个问题？更进一步是说，Seller和Buyer如何确保算法在SGX上运行的？**
   1. **目前尚未找到解决办法**。
7. Buyer的Algorithm被Seller感知，如何解决这个问题？
   1. 上传在智能合约中，不上传源代码，暂时可以认为外部无法感知合约内容。
8. 如何保证Algorithm窃取seller的数据，如何阻止Trust和buyer合谋窃取数据？
   1. 禁止该算法调用CALL/CALLCODE的功能与其他合约通信。
   2. 对输出数据收费，输出数据越多，费用越高，如果直接窃取全部数据，相当于付出整个版权费。
   3. 如果想进一步限制，可以考虑libdft或者CloudFence跟踪流入数据，并且禁止输出原始数据。不过本文未做进一步工作。
9. 如何保证Algorithm的结果不被窃取？
   1. SGX运行完结果后，使用$SK_{enclave}$对ID， 输入数据大小、运行结果哈希，gas消耗的和，合约执行状态(成功/失败)进行签名，连同这些数据一起发送给DTMC.
   2. DTMC使用$Pub_{enclave}$对签名进行验证，以证明数据没有被篡改。
10. 如何保证buyer使用服务之后付钱？
    1. buyer部署Algorithm合约后需要在DTMC提供offer以及对seller和trust node的报酬。
    2. seller和trust node在执行之前检查报酬是否满足要求。
    3. seller和trust node在执行期间发送执行指令，在此期间可以禁止报酬被修改。
11. 如何保证Seller重复发送数据？如何保证数据质量？
    1. buyer只能对程序运行结果设置上限，防止seller发送太多重复数据。
    2. **数据质量无法保证。**
12. Trust nodes 的remote attestation 过程存在作恶的可能性嘛？
13. **一个Bug**
    1. Buyer预存一些费用，但是智能合约中将全部或者部分原始数据输出，此时会以非常小的代价获取到原始数据。

## 一个标准的数据服务交易系统

### 参与角色

- Buyer：拥有自己的数据分析算法，需要数据进行分析。
- Seller：向Buyer提供数据分析服务。
- 数据计算服务系统：结合Seller提供的原始数据和Buyer的算法，进行数据分析服务。
- 结算系统: 负责Buyer和Seller的数据服务交易结算。

### 系统特性

- 正确运行Buyer的算法，确保Buyer的算法不被篡改。【SDTE---------√】
- Buyer的数据分析结果不被泄露、篡改。【SDTE---------√】

- buyer对请求的服务支付必要的报酬。【SDTE---------√】
- Seller可以得到应有的报酬。【SDTE---------√】
- Seller拥有数据的绝对控制权。【SDTE---------**x**】**SDTE中数据上链，存在数据泄露的风险**
- Seller的数据在数据计算服务过程中不会被泄露和篡改。【SDTE---------**x**】**SDTE输出数据收费，存在泄漏的可能性**
- 具有高性能、支持复杂的分析算法。【SDTE---------**x**】**SDTE使用智能合约类型的分析算法，智能合约不支持浮点数，计算性能低效**
- Buyer的数据运行算法不会被泄露。【SDTE---------**x**】**SDTE使用智能合约类型的分析算法，Seller可以在非SGX环境下再次重复执行**

