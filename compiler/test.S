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
.global f
.thumb
.thumb_func
.type f, %function
f:
sub sp, sp, #4
push {r3, r4, r7, lr}
add	r7, sp, #16
ldr r3, [r7, #0]
sub r4, r3, #1
push {r4}
bl f(PLT)
add sp, sp, #4
mov r3, r0
mov r0, r3
b .f.ret
.f.ret:
pop {r3, r4, r7, pc}
add sp, sp, #4
bx lr
.size f, .-f

.align 1
.global main
.thumb
.thumb_func
.type main, %function
main:
sub sp, sp, #8
push {r3, r4, r7, lr}
add	r7, sp, #16
mov r3, #1
str r3, [r7, #0]
mov r3, #11
str r3, [r7, #4]
mov r3, #1
push {r3}
bl f(PLT)
add sp, sp, #4
mov r4, r0
.main.ret:
pop {r3, r4, r7, pc}
add sp, sp, #8
bx lr
.size main, .-main


