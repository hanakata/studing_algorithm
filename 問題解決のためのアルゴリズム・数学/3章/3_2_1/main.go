package main

import (
	"fmt"
	"time"
)

func gcd(n int, m int) {
	ans := 0
	check := m
	if n < m {
		check = n
	}

	for i := 1; i <= check; i++ {
		if n%i == 0 && m%i == 0 {
			ans = i
		}
	}
	fmt.Println(ans)
}

func main() {
	now := time.Now()
	gcd(33, 88)
	fmt.Printf("time: %vs\n", time.Since(now).Seconds())
}
