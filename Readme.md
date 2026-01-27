### Testing RVV32 Vector Operations in Qemu  

## Installing 
Create a Directory on your Linux System   
```
mkdir -p ${HOME}
git clone ---v--recursive git@github.com:rajvishmips/qemu-vector-test.git
```
If it has issues cloning qemu, 
```
rm -rf qemu
cd qemu
git clone https://gitlab.com/qemu-project/qemu.git
```

## Build qemu
```
cd qemu
./configure --target-list=riscv32-softmmu,riscv32-linux-user 
make -j ${nproc}
```

## run Vector tests
`cd ${HOME}/qemu-vector-test/vector_test`
Adjust the variables in run.sh and
`sh run.sh` to test the avaiable tests


