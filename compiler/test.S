	.arch armv7-a
.fpu vfpv3-d16
.eabi_attribute 28, 1
.eabi_attribute 20, 1
.eabi_attribute 21, 1
.eabi_attribute 23, 3
.eabi_attribute 24, 1
.eabi_attribute 25, 1
.eabi_attribute 26, 2
.eabi_attribute 30, 6
.eabi_attribute 34, 1
.eabi_attribute 18, 4
.data

.text
.align 1
.global main
.thumb
.thumb_func
.type main, %function
main:
sub sp, sp, #4
push {r4, r7, lr}
add	r7, sp, #12
movw r4, #0
movt r4, #17096
str r4, [r7, #0]
movw r4, #0
movt r4, #17096
str r4, [r7, #0]
mov r0, #1
b .main.ret
.main.ret:
pop {r4, r7, pc}
add sp, sp, #4
bx lr
.size main, .-main


