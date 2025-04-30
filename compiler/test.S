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
.syntax unified 
.thumb
.thumb_func
.type main, %function
main:
sub sp, sp, #8
push {r4, r5, r6, r7, r8, lr}
add	r7, sp, #24
add r5, r7, #0
add r4, r5, #0
mov r5, #1
str r5, [r4]
add r6, r7, #0
add r5, r6, #4
mov r6, #2
str r6, [r5]
add r8, r7, #0
add r6, r8, #0
ldr r8, [r6]
mov r0, r8
b .main.ret
.main.ret:
pop {r4, r5, r6, r7, r8, pc}
add sp, sp, #8
bx lr
.size main, .-main


