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
.L0:
	.space 16
.text
.align 1
.global f
.syntax unified 
.thumb
.thumb_func
.type f, %function
f:
sub sp, sp, #0
push {r4, r5, r6, r7, lr}
add	r7, sp, #20
ldr r4, [r7, #0]
add r5, r4, #4
ldr r4, [r7, #0]
add r6, r4, #4
ldr r4, [r6]
add r6, r4, #1
str r6, [r5]
ldr r4, [r7, #0]
add r6, r4, #0
ldr r4, [r6]
mov r0, r4
b .f.ret
.f.ret:
pop {r4, r5, r6, r7, pc}
add sp, sp, #0
bx lr
.size f, .-f

.align 1
.global ff
.syntax unified 
.thumb
.thumb_func
.type ff, %function
ff:
sub sp, sp, #0
push {r4, r5, r7, lr}
add	r7, sp, #16
ldr r4, [r7, #0]
add r5, r4, #8
mov r0, r5
push {r5}
bl f(PLT)
add sp, sp, #4
mov r4, r0
.ff.ret:
pop {r4, r5, r7, pc}
add sp, sp, #0
bx lr
.size ff, .-ff

.align 1
.global main
.syntax unified 
.thumb
.thumb_func
.type main, %function
main:
sub sp, sp, #0
push {r4, r5, r6, r7, r8, r9, r10, r11, lr}
add	r7, sp, #36
ldr r5, =.L0
add r4, r5, #0
mov r5, #10
str r5, [r4]
ldr r6, =.L0
add r5, r6, #4
mov r6, #2
str r6, [r5]
ldr r8, =.L0
add r6, r8, #8
mov r8, #2
str r8, [r6]
ldr r9, =.L0
add r8, r9, #12
mov r9, #4
str r9, [r8]
ldr r9, =.L0
mov r0, r9
push {r9}
bl ff(PLT)
add sp, sp, #4
mov r10, r0
ldr r11, =.L0
add r9, r11, #12
ldr r11, [r9]
mov r0, r11
b .main.ret
.main.ret:
pop {r4, r5, r6, r7, r8, r9, r10, r11, pc}
add sp, sp, #0
bx lr
.size main, .-main


