package main

import (
	"fmt"
	"time"
)

func isPrime(n int) bool {
	//ルートnまで調べれば素数かは判断可能
	for i := 2; i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

func main() {
	now := time.Now()
	if isPrime(400) {
		fmt.Println("Prime")
	}
	fmt.Printf("time: %vs\n", time.Since(now).Seconds())
}
