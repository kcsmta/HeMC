## Install OpenFHE
Follow this [official repo](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/linux.html).
It is recommended to download and build the library in a partition with sufficient storage space.

### Install dependencies
The OpenFHE library requires `g++`, `cmake` and `make` which should be installed before you come here. 

### Install OpenFHE
(Move to a partition with sufficient storage space.)
```
$ git clone https://github.com/openfheorg/openfhe-development.git
$ cd openfhe-development
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

After running above commands, you can see the folder `openfhe` inside the folder `/usr/local/include/`, and `libOPENFHE[module].so.[version]` libraries in `/user/local/lib`. Once the `OpenFHE` installed, you can use the `OpenFHE` in your code.

## Code HeMC
### Step 1: Write CMakeLists.txt
Use the `CMakeLists.txt` file for your project (modify appropriate information if needed).

### Step 2: Write your code
See `main.cpp`. 

### Step 3: Build your code
```
$ mkdir build && cd build
$ cmake ..
$ make
```

### Step 4: Run your code
```
$ ./verify-sign
$ ./verify-range
```