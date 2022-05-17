# FORKING

## Introduction
The following document details all the locations where code needs to be changed in order to create a fork of TurtleCoin and by extension BillyBucks. The changes are ordered by file name where the directory assumes you are in the root of the BillyBucks Blockchain repository

## The GENESIS_COINBASE_TX_HEX Process.
In order to generate the Genesis hash you first need to do all the changes detailed below and build the deployables using the instructions in [Deployment.md](Deployment.md).
Then you need to run the BillyBucksd executable with the --print-gensis-tx argument:
> ./BillyBucksd --print-gensis-tx

This will display the genesis TX which can then be copied into the CryptoNoteConfig file. You will then need to rebuild the deployables.


## src/config/CryptoNoteConfig.h
```text
Change the Difficulty_Target
    Number of seconds between blocks being mined (AVG)
    recommended: 30 or 60

Change the CRYPTONOTE_Public_Address_Base58_Prefix
    This is the letter prefix for wallet address that will be at the start. BillyBucks use BT
    The cryptonote site has a [tool](https://cryptonotestarter.org/tools.html) for creating these

Change the mined money window
    This determines how many blocks need to pass for rewards to enter wallets
    Time = This_value * Difficulty_Target(seconds)

Changed the Change the ZAWY_DIFFICULTY_BLOCK_INDEX
    This determines what block the difficulty function is upgraded.
    Set this to 0 to use the best/newest function out of the gate

Change the LWMA_2_DIFFICULTY_BLOCK_INDEX (+V2/+V3)
    These should increment from 1 -> 3

Change the GENESIS_COINBASE_TX_HEX
    This is generated after compiling the source code and running the daemon with --print-gensis-tx
    Instructions can be found at the top of this document.

Change the MIXIN_LIMITS_Vx_HEIGHT 
    Mixin is used by cryptonote currencies to improve privacy of transations.
    This value determines how many miners need to be waiting to process a transaction before it can occur in a batch.
    For small networks it is advised to use 0, 1, 2 (incrementing by 1) but for large network increaseing this may be a good idea

Change the MINIMUM_MIXIN_Vx (x = 1, 2, 3) values:
    This is the actual number of miners used at the different MIXIN_Hights. 
    For a small or test network setting these to 0 is preferable

Change the DEFAULT_MIXIN_Vx (x = 1, 2, 3) values:
    For a small network it is again preferable to se these to 0 or the MINIMUM_MIXIN_Vx.
    >         const uint64_t DEFAULT_MIXIN_V1 = MINIMUM_MIXIN_V1;

Change the UPGRADE_HEIGHT_Vx s
    Can just increment by 1 or bigger bounds to give more time using older functions
    Older mining functions allowed ASICS so if you want to quickyl bootstrap the network large jumps may be a good idea

Change UPGRADE_HEIGHT_CURRENT:
    dependent on which mining algorithm you want to use It can be beneficial to set this = to the highest upgrade heigh variable.
    Essentially this will determine which algorithm is used to mine the currecnny when you start the blockchain.

Delete the FORK_HEIGHTS from the FORK_HEIGHTS array

Change the SOFTWARE_SUPPORTED_FORK_INDEX to 0
    This is used to inform users when their mining software is out of date.
    And will need to be incremented every major update to the software.

Change the Crypto_Name to the desired name of your cryptocurrency

Change the DEFAULT_PORT (s) to a unique port number. 
    Each port should be different.
    P2P_DEFAULT_PORT = Used by the daemon to find and interact with other nodes
    RPC_DEFAULT_PORT = Used by applications such as mining pool software to connect to the daemon using the RPC Api
    SERVICE_DEFAULT_PORT = Used by the wallet-api daemon

Change the CRYPTONOTE_NETWORK ID
    This is a 16 long array of random hexadecimal character used to identify blockchains.
    Your altered list needs to be 16 Characters Long

Change the seed nodes
    Change the Seed Nodes IP. The Deployment.MD of this repository has more infromation of this process.
```

## src/config/WalletConfig.h
```text
Change the address prefix
    Should be the same as the CRYPTONOTE_Public_Address_Base58_Prefix used in the above config but in ascii for.
    So in the BillyBucks case this would be BT
    This is case sensitive
Change the Ticker
    This can be anything you want, it is used by some softwares to display the shortened token name
Change the daemonName
    This is whatever the compiled Daemon is called. If you have change the compile name of the daemon in .... this would need to reflect that change
Change the walletdName
    This is the name of the service (can be anything)
    currently using BillyBucks-service
Might need to change the standardAddressLength
    You can test this by compiling the code and then running the wallet program
    ./zedwallet
    After creating a new wallet you can put the address into the miner and it will warn you if the wallet address is the wrong length.
```

## src/config/version.h
```
Change the PROJECT_NAME to the name of your token
Change the APP_VER_MAJOR to 0
```
----
With the above changes you have successfully forked TurtleCoin/BillyBucks into a new cryptocurrency to build the dependencies and deploy your blockchain look at the instructions within the [DEPLOYMENT.md File](DEPLOYMENT.md)

----

# Fixing the --allow-local-ip call
If forking from TurtleCoin and needing to use the --allow-local-ip commandline argument it may be necessary to implement a bug fix.
Within **src/daemon/DaemonConfiguration.cpp** you can find the following code
```c++
if (cli.count("local-ip") > 0)
{
    config.localIp = cli["local-ip"].as<bool>();
}
```
This must be changed to 
```c++
if (cli.count("allow-local-ip") > 0)
{
    config.localIp = cli["allow-local-ip"].as<bool>();
}
```