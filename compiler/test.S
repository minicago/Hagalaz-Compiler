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
.syntax unified 
.thumb
.thumb_func
.type f, %function
f:
sub sp, sp, #0
push {r4, r5, r6, r7, lr}
add	r7, sp, #20
ldr r4, [r7, #0]
cmp r4, #1
ite eq
moveq r5, #1
movne r5, #0
uxtb r5, r5
cmp r5, #0
bne .L4
b .L5
.L4:
mov r0, #1
b .f.ret
.L5:
ldr r4, [r7, #0]
cmp r4, #2
ite eq
moveq r5, #1
movne r5, #0
uxtb r5, r5
cmp r5, #0
bne .L8
b .L9
.L8:
mov r0, #1
b .f.ret
.L9:
ldr r4, [r7, #0]
sub r5, r4, #1
mov r0, r5
push {r5}
bl f(PLT)
add sp, sp, #4
mov r4, r0
ldr r5, [r7, #0]
sub r6, r5, #2
mov r0, r6
push {r6}
bl f(PLT)
add sp, sp, #4
mov r5, r0
add r6, r4, r5
mov r0, r6
b .f.ret
.f.ret:
pop {r4, r5, r6, r7, pc}
add sp, sp, #4
bx lr
.size f, .-f

.align 1
.global main
.syntax unified 
.thumb
.thumb_func
.type main, %function
main:
sub sp, sp, #0
push {r4, r5, r7, lr}
add	r7, sp, #16
mov r4, #5
mov r0, r4
push {r4}
bl f(PLT)
add sp, sp, #4
mov r5, r0
mov r0, r5
b .main.ret
.main.ret:
pop {r4, r5, r7, pc}
add sp, sp, #0
bx lr
.size main, .-main


