; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds [2 x i32], ptr %3, i64 0
  %5 = getelementptr inbounds [2 x i32], ptr %4, i64 0, i64 0
  %6 = load i32, ptr %5, align 4
  ret i32 %6
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca [2 x [2 x i32]], align 16
  store i32 0, ptr %1, align 4
  store i32 1, ptr %2, align 4
  store i32 4, ptr %3, align 4
  %5 = getelementptr inbounds [2 x [2 x i32]], ptr %4, i64 0, i64 0
  %6 = getelementptr inbounds [2 x i32], ptr %5, i64 0, i64 0
  store i32 114, ptr %6, align 4
  %7 = getelementptr inbounds i32, ptr %6, i64 1
  store i32 514, ptr %7, align 4
  %8 = getelementptr inbounds [2 x i32], ptr %5, i64 1
  %9 = getelementptr inbounds [2 x i32], ptr %8, i64 0, i64 0
  %10 = load i32, ptr %3, align 4
  %11 = load i32, ptr %2, align 4
  %12 = add nsw i32 %10, %11
  store i32 %12, ptr %9, align 4
  %13 = getelementptr inbounds i32, ptr %9, i64 1
  store i32 810, ptr %13, align 4
  %14 = getelementptr inbounds [2 x [2 x i32]], ptr %4, i64 0, i64 1
  %15 = getelementptr inbounds [2 x i32], ptr %14, i64 0, i64 0
  %16 = load i32, ptr %15, align 8
  %17 = getelementptr inbounds [2 x [2 x i32]], ptr %4, i64 0, i64 0
  %18 = getelementptr inbounds [2 x i32], ptr %17, i64 0, i64 0
  %19 = load i32, ptr %18, align 16
  %20 = icmp sgt i32 %16, %19
  br i1 %20, label %21, label %24

21:                                               ; preds = %0
  %22 = getelementptr inbounds [2 x [2 x i32]], ptr %4, i64 0, i64 0
  %23 = call i32 @foo(ptr noundef %22)
  store i32 %23, ptr %1, align 4
  br label %25

24:                                               ; preds = %0
  store i32 2, ptr %1, align 4
  br label %25

25:                                               ; preds = %24, %21
  %26 = load i32, ptr %1, align 4
  ret i32 %26
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
