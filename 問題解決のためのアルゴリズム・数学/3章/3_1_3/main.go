package main

import (
	"fmt"
	"time"
)

func isdivisor(n int) {

	for i := 2; i*i <= n; i++ {
		if n%i == 0 {
			fmt.Println(i)
		}
		if i != n/i {
			fmt.Println(n / i)
		}
	}
}

func main() {
	now := time.Now()
	isdivisor(100)
	fmt.Printf("time: %vs\n", time.Since(now).Seconds())
}
