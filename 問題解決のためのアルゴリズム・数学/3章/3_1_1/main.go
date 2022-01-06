package main

import (
	"fmt"
	"time"
)

func isPrime(n int) bool {
	for i := 2; i < n; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

func main() {
	now := time.Now()
	if isPrime(402031) {
		fmt.Println("Prime")
	}
	fmt.Printf("time: %vs\n", time.Since(now).Seconds())
}
