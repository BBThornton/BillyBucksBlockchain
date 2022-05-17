# BillyBucks Deployment
Currently BillyBucks is set up to support the pay-as-you-go browser-based mining ecosystem which it was designed for the following document details how to build the deployables for BillyBucks as well instructions on how to configure the deployment environment. Some of this documentation is based on the documentation of the TurtleCoin repositories [COMPILE.md](COMPILE.md).

## Development Requirements For Ubuntu Linux
It is heavily advices to use linux as both your deployment and development environment. This is also the only environment which I have personally tests.

In order to develop on windows I would advice you to use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install) which will allow you to run linux on your native windows environment. Alternatively a Virtual Machine would also work.

All of these instructions assume you are running on **Ubuntu 18.04**, NOTE: this is not the latest version of Ubuntu.

### Build Dependencies
**Note:** Individual names for these packages may differ depending on your Linux distribution.

-   [Boost](https://www.boost.org/)
-   [OpenSSL](https://www.openssl.org/)
-   [Cmake (3.8, higher)](https://cmake.org/download/)
-   [GNU Make](https://ftp.gnu.org/gnu/make/)
-   [Git](https://git-scm.com/)
-   [GCC 7, higher](https://gcc.gnu.org/) or [CLANG 6, higher](https://clang.llvm.org/)

### Dependency install commands for Ubuntu
-   `sudo apt update`
-   `sudo apt install -y libboost-all-dev libssl-dev gcc-8 g++-8 cmake`
-   `export CC=gcc-8`
-   `export CXX=g++-8`

## BillyBucks Build Commands for Ubuntu
In order to run these commands you should first clone this repository into your working directory
-   `git clone -b master --single-branch https://github.com/BBThornton/BillyBucksBlockchain`

Then you are able to run the build commands:
-   `cd BillyBucksBlockchain`
-   `mkdir build`
-   `cd build`
-   `cmake ..`
-   `make`

This will create a number of executables in the SRC folder including:
- BillyBucksd = The BillyBucks Daemon
- miner = The generic BillyBucks miner
- zedwallet = The BillyBucks Wallet Software
- wallet-api = The Json provider for the wallet api functionality

## BillyBuck Deployment
The BillyBucks mining daemon must be running on at leas 3 independent machines in order to constitute a blockchain network.
In order to achieve this you must provision independent machine or use a series of bridged-network virtual machines.

### Seed nodes
Once you have provisioned you 3 machines you must select two of them and node their IP addresses these will be used as the networks seed nodes, nodes responsible for allowing nodes to discover each other in the network.
You must then go to the /src/config/CryptoNoteConfig.h file within the BillyBucks repository and replace the SEED_NODES[] ips with the IPs of your chose severs. It should look something like this.
``` c++
const char *const SEED_NODES[] = {
        "192.168.1.111:22221",//Node1
        "192.168.1.112:22221", //Node2
    };
```
Where the 22221 port is the P2P_DEFAULT_PORT of the BillyBucks Daemon.
Once you have set your seed nodes IP you must then rebuild the deployables using the commands detailed [above](#billybucks-build-commands-for-ubuntu).

Once complete you must copy the entire contents of the build/src folder onto your seed node server and also ensure you have installed the dependencies.
After copying you can then execute the BillyBucksDaemon using the following Command
```
 ./BillyBucksd
```
If you are using virtual machines or all of your servers are on the same local network you must also append the --allow-local-ip argument and it may also be beneficial to use the log-level argument to improve the verbosity.
```
    ./BillyBucksd --allow-local-ip --log-level 4
```
**You are now officially running BillyBucks Node.**

Repeat this process of the other two servers and you will have a functional cryptocurrency.
