BASEDIR=..
QEMU32=${BASEDIR}/qemu/build/qemu-riscv32
#QEMU=${BASEDIR}/qemu/build/qemu-riscv64
${QEMU32} -cpu rv32,c=off,zce=on,zicond=true,v=true,vlen=1024   rvv
