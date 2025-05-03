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
sub sp, sp, #164
push {r4, r5, r6, r7, lr}
add	r7, sp, #20
add r5, r7, #0
add r4, r5, #0
mov r5, #1
str r5, [r4]
add r5, r7, #0
add r4, r5, #4
mov r5, #2
str r5, [r4]
add r5, r7, #0
add r4, r5, #0
mov r5, #3
str r5, [r4]
add r5, r7, #0
add r4, r5, #4
mov r5, #4
str r5, [r4]
add r5, r7, #0
add r4, r5, #0
mov r5, #7
str r5, [r4]
mov r4, #3
str r4, [r7, #32]
add r5, r7, #68
add r4, r5, #0
mov r5, #1
str r5, [r4]
add r5, r7, #68
add r4, r5, #4
mov r5, #2
str r5, [r4]
add r5, r7, #68
add r4, r5, #8
mov r5, #3
str r5, [r4]
add r5, r7, #68
add r4, r5, #12
mov r5, #4
str r5, [r4]
add r5, r7, #68
add r4, r5, #16
mov r5, #5
str r5, [r4]
add r5, r7, #68
add r4, r5, #20
mov r5, #6
str r5, [r4]
add r5, r7, #68
add r4, r5, #24
mov r5, #7
str r5, [r4]
add r5, r7, #68
add r4, r5, #28
mov r5, #8
str r5, [r4]
add r5, r7, #100
add r4, r5, #0
mov r5, #1
str r5, [r4]
add r5, r7, #100
add r4, r5, #4
mov r5, #2
str r5, [r4]
add r5, r7, #100
add r4, r5, #0
mov r5, #3
str r5, [r4]
add r5, r7, #100
add r4, r5, #0
mov r5, #5
str r5, [r4]
add r5, r7, #0
add r4, r5, #24
ldr r5, [r4]
add r5, r7, #100
add r4, r5, #0
str r5, [r4]
add r5, r7, #100
add r4, r5, #4
mov r5, #8
str r5, [r4]
add r5, r7, #100
add r4, r5, #20
ldr r5, [r4]
add r5, r7, #132
add r4, r5, #0
str r5, [r4]
add r5, r7, #68
add r4, r5, #20
ldr r5, [r4]
add r5, r7, #132
add r4, r5, #0
str r5, [r4]
add r5, r7, #132
add r4, r5, #0
mov r5, #3
str r5, [r4]
add r5, r7, #132
add r4, r5, #4
mov r5, #4
str r5, [r4]
add r5, r7, #132
add r4, r5, #0
mov r5, #5
str r5, [r4]
add r5, r7, #132
add r4, r5, #4
mov r5, #6
str r5, [r4]
add r5, r7, #132
add r4, r5, #0
mov r5, #7
str r5, [r4]
add r5, r7, #132
add r4, r5, #4
mov r5, #8
str r5, [r4]
add r5, r7, #132
add r4, r5, #28
ldr r5, [r4]
add r5, r7, #132
add r4, r5, #0
ldr r5, [r4]
add r4, r5, r5
add r6, r7, #132
add r5, r6, #4
ldr r6, [r5]
add r5, r4, r6
add r6, r7, #100
add r4, r6, #24
ldr r6, [r4]
add r4, r5, r6
mov r0, r4
b .main.ret
.main.ret:
pop {r4, r5, r6, r7, pc}
add sp, sp, #164
bx lr
.size main, .-main


