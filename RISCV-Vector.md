# RISC-V Vector Extension
## Introduction

RISC-V Vector extensions defines the new instruction set extensions for the RISCV ISA. This extension adds 32 Vector instructions. This is like a SIMD instruction for the x86 platform  with some important differences. The following table captures the basic difference between the x86 SIMD and the RVV 1.0 spec.
 
| Feature      | x86 SIMD                  | RISCV RVV               |
|--------------|---------------------------| ------------------------| 
| Vector Width | Fixed(128/256/512)        | Scalable                |
| Vector Length| Known at compile time     | Unknown at compile time | 
| Loop Width   | Strip mining by compiler  | Hardware Strip Mining   | 
| Masking      | Onlyu available on AVX-512| Native                  |
| Portability  | Per width Tuning          | Portable across VLEN    | 

## Global parameters affecting the RVV Implementation
**vl**  - Vector Lenth. This defines the number of elements on which the next vector operation will be
 executed. The element before the vl mark are part of the vector head and the element past vl arepart 
 of the tail.  
   
**SEW** The Selected Element Width in bits for input and output vectors.  
  
**LMUL** Group Multiplier. It defines the number of vector registers forming a group, effectively 
changing teh number of elements you can operate on per instruction. 
The default is one register per group. By grouping multiple registers together, you can process more elements per instruction. LMUL can be (1,2,4,8,1/2,1/4,1/8).  
**ELEN** The hardware ceiling on how wide each element will be. Typically it is 64.  
By definition,  **SEW/LMUL <=ELEN** 
  
**Tail Policies** As defined earlier, elements past VLEN are considered a part of the tail.
RVV defines two policies regarding the tail; *undisturbed* and *agnostic*.
In undisturbed,the tail elements are untouched and in the agnostic, tail elements could be
left alone or filed with 1's.  


**Masking** Most RVV operations accept an extra mask operand. It is a bitmask vector that defined what 
elements should be operted on.  
For example, a mask of [1,0,1,0,1,0,1,0] will operate only on odd elements.
Like tail, RVV defines two mask policies - *undisturbed* and *ignore*. In undisturbed, the 
masked off elements are untouched and in the agnostic, masked off elements could be left alone or 
filed with 1's.

## Data Types in RVV Implementation
### Integer data types
Int8,Int16,Int32, Int64 (It supports both signed and unsigned).  
### Floating Point data types
 float16 (fp16/half), float32 (fp32/single) and float64(fp64/double)
The distinction between signed and unsigned is determined by the instruction. For example,*vmul.vv* is a signed multiply and *vmulhu.vv* is a unsigned multiply. *vfmul.vv* is a floating point multiply.  
### Widening  
In addition to the basic opernds RVV also supports conversion abnd widening operations. Integer elements can be converted to float and vice versa and it supports widening two fp16 multiplications to a wider fp32 elements.  

## RVV Operations summary
Here are the various operations that are defined by RVV 1.0. They are defined by the various parameters and policies defined before.

### Basic
**vsetvli** - Set Vector Length SEW,LMUL  
**vsetivli** - Same but set it with an immediate value

### Integer  Arithmetic
Vector Arithmetic supports the following operations.
- Add/Subtract - vadd,vsub,vrsub  
- Multiply - vmul, vmulh, vmulhu, vmulhsu
- Divide/Reminder - vdiv, vdivu, vrem, vremu  
- Widening Multiply - vwmul, vwmulu, vwmulsu
- Add with carry - vadc, vmadc
- Sub with borrow - vsbc, vmsbc  
- Saturating - vsadd, vssub, vsaddu, vssubu

### Floating Point Arithmetic
- Add/Sub/Mul/Div - vfadd, vfsub, vfmul, vfdiv  
- Fused multiply-add - vfmacc, vfmadd, vfnmacc, vfnmadd  
- Widening  - vfwadd, vfwmul, vfwmacc  
- Misc - vfsqrt, vfmin, vfmax, vfsgnj  

### Bitwise & Shift
- Logical - vand, vor, vxor, vnot  
- Shift - vsll, vsrl, vsra  
- Narrowing Shift - vnsrl, vnsra  

### Compare and Mask
- Integer Mask - vmseq, vmsne, vmslt, vmsltu, vmsle, vmsleu, vmsgt, vmsgtu  
- Float compare - vmfeq, vmfne, vmflt, vmfle, vmfgt, vmfge  
- Mask Logical - vmand, vmor, vmxor, vmnand, vmnor, vmxnor  
- Population Count - vcpop
- Find first set - vfirst  

## Reduction
- Integer - vredsum, vredmin, vredmax, vredand, vredor, vredxor  
- Unsigned - vredminu, vredmaxu  
- Float - vfredsum, vfredmin, vfredmax  
- Widening - vwredsum, vwredsumu

## Permute & Slide
- Slide up/Down - vslideup, vslidedown  
- Slide by 1 - vslide1up, vslide1down  
- Gather - vrgather, vrgatherei16 
- Compress - vcompress  
- Move - vmv.v.v, vmv.v.x, vmv.v.i  
- Whole register move - vmv1r.v … vmv8r.v

## Type Conversion 
- Int <->Float - vfcvt.f.x, vfcvt.x.f  
- Widen int→float - vfwcvt.f.xu, vfwcvt.f.x  
- Narrow float - vfncvt.f.f, vfncvt.x.f  
- Widen/narrow int - vzext.vf2/4/8, vsext.vf2/4/8  

Thse operands can be suffixed to denote the operands  
- .vv - Vector <op> Vector
- .vx - Vector <op> Scalar (GPR)  
- .vf - Vector <op> Scalar (FPR)
- .vi - Vector <op> Immediate 
- .wv/.wx - Wide source operand









