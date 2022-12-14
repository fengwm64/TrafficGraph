//  StatusCode

#pragma once
typedef int Status;        // 函数类型，用于查询函数结果状态代码
// 函数结果状态
#define    TRUE            1			// 真
#define    FALSE           0			// 假
#define    OK               1			// 成功
#define    ERROR           0		// 错误
#define    INFEASIBLE      -1	// 不可行
#define    OVERFLOW        -2	// 溢出