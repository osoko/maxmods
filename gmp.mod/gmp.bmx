' Copyright (c) 2009 Bruce A Henderson
' 
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
' 
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
' 
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.
'
SuperStrict


Rem
bbdoc: GNU Multiple Precision arithmetic library.
End Rem
Module BaH.GMP

ModuleInfo "Version: 1.00"
ModuleInfo "License: MIT"
ModuleInfo "Copyright: GMP - 1991-2009 Free Software Foundation"
ModuleInfo "Copyright: Wrapper - 2009 Bruce A Henderson"

ModuleInfo "History: 1.00"
ModuleInfo "History: Initial Release."

?macos
ModuleInfo "LD_OPTS: -L%PWD%/lib/macos"
?win32
ModuleInfo "LD_OPTS: -L%PWD%/lib/win32"
?linux
' TODO
?

Import "common.bmx"


Rem
bbdoc: A GMP integer.
about: Used for performing integer arithmetic.
End Rem
Type GMPInt

	Field gmpPtr:Byte Ptr
	
	Function _create:GMPInt(gmpPtr:Byte Ptr)
		If gmpPtr Then
			Local this:GMPInt = New GMPInt
			this.gmpPtr = gmpPtr
			Return this
		End If
	End Function

	Rem
	bbdoc: Creates and initialised a new GMPInt.
	End Rem
	Function Init:GMPInt()
		Local this:GMPInt = New GMPInt
		this.gmpPtr = bmx_gmp_mpz_init()
		Return this
	End Function
	
	Rem
	bbdoc: Sets the value from @op.
	End Rem
	Method Set(op:GMPInt)
		bmx_gmp_mpz_set(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: Sets the value from @op.
	End Rem
	Method SetInt(op:Int)
		bmx_gmp_mpz_setint(gmpPtr, op)
	End Method
	
	Rem
	bbdoc: Sets the value from @op.
	about: @op is truncated to make it an integer.
	End Rem
	Method SetDouble(op:Double)
		bmx_gmp_mpz_setdouble(gmpPtr, op)
	End Method
	
	Rem
	bbdoc: Sets the value from @op.
	about: @op is truncated to make it an integer.
	End Rem
	Method SetRational(op:GMPRational)
		bmx_gmp_mpz_setrational(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: Sets the value from @op.
	about: @op is truncated to make it an integer.
	End Rem
	Method SetFloat(op:GMPFloat)
		bmx_gmp_mpz_setfloat(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: Sets the value from a String, in base @base.
	about: The default is base 10.
	<p>
	White space is allowed in the string, and is simply ignored.
	</p>
	<p>
	The base may vary from 2 to 62, or if base is 0, then the leading characters are used: 0x and 0X for hexadecimal, 0b and 0B for binary, 0 for octal,
	or decimal otherwise.
	</p>
	<p>
	For bases up to 36, case is ignored; upper-case and lower-case letters have the same value. For bases 37 to 62, upper-case letter represent the usual
	10..35 while lower-case letter represent 36..61.
	</p>
	<p>
	This method returns 0 if the entire string is a valid number in base base. Otherwise it returns −1.
	</p>
	End Rem
	Method SetStr:Int(s:String, base:Int = 10)
		Return bmx_gmp_mpz_setstr(gmpPtr, s, base)
	End Method
	
	Rem
	bbdoc: Swaps this value with @op efficiently.
	End Rem
	Method Swap(op:GMPInt)
		bmx_gmp_mpz_swap(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: If the value fits into a an int returns the value.
	about: Otherwise returns the least significant part of the value, with the same sign.
	<p>
	If the value is too big to fit in an int, the returned result is probably not very useful. To find out if the value will fit, use the function FitsInt().
	</p>
	End Rem
	Method GetInt:Int()
		Return bmx_gmp_mpz_getint(gmpPtr)
	End Method
	
	Rem
	bbdoc: Returns as a double, truncating if necessary (ie. rounding towards zero).
	about: If the exponent from the conversion is too big, the result is system dependent. An infinity is returned where available.
	A hardware overflow trap may or may not occur.
	End Rem
	Method GetDouble:Double()
		Return bmx_gmp_mpz_getdouble(gmpPtr)
	End Method
	
	Rem
	bbdoc: Returns as a double, truncating if necessary (ie. rounding towards zero), and returning the exponent separately.
	about: The return value is in the range 0.5<=abs(d)<1 and the exponent is stored to *exp. d * 2^exp is the (truncated) op value.
	If op is zero, the return is 0.0 and 0 is stored to *exp.
	<p>
	This is similar to the standard C frexp
	</p>
	End Rem
	Method GetDouble2Exp:Double(_exp:Int Var)
		Return bmx_gmp_mpz_getdouble2exp(gmpPtr, Varptr _exp)
	End Method
	
	Rem
	bbdoc: Returns a string of digits in base @base.
	about: The @base argument may vary from 2 to 62 or from −2 to −36. The default is 10.
	<p>
	For base in the range 2..36, digits and lower-case letters are used; for −2..−36, digits and upper-case letters are used; for 37..62, digits,
	upper-case letters, and lower-case letters (in that significance order) are used.
	</p>
	End Rem
	Method GetStr:String(base:Int = 10)
		Return bmx_gmp_mpz_getstr(gmpPtr, base)
	End Method
	
	Rem
	bbdoc: Adds @op to this value, returning the result.
	End Rem
	Method Add:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_add(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: Adds @op to this value, returning the result.
	End Rem
	Method AddInt:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_addint(gmpPtr, op))
	End Method
	
	Rem
	bbdoc: Subtracts @op from this value, returning the result.
	End Rem
	Method Sub:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_sub(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: Subtracts @op from this value, returning the result.
	End Rem
	Method SubInt:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_subint(gmpPtr, op))
	End Method
	
	Rem
	bbdoc: Subtracts this value from @op, returning the result.
	End Rem
	Method IntSub:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_intsub(gmpPtr, op))
	End Method
	
	Rem
	bbdoc: Multiplies value by @op, returning the result.
	End Rem
	Method Mul:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_mul(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: Multiplies value by @op, returning the result.
	End Rem
	Method MulInt:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_mulint(gmpPtr, op))
	End Method
	
	Rem
	bbdoc: Adds the result of @op1 multplied by @op2, to this value.
	End Rem
	Method AddMul(op1:GMPInt, op2:GMPInt)
		bmx_gmp_mpz_addmul(gmpPtr, op1.gmpPtr, op2.gmpPtr)
	End Method
	
	Rem
	bbdoc: Adds the result of @op1 multplied by @op2, to this value.
	End Rem
	Method AddMulInt(op1:GMPInt, op2:Int)
		bmx_gmp_mpz_addmulint(gmpPtr, op1.gmpPtr, op2)
	End Method
	
	Rem
	bbdoc: Subtracts the result of @op1 multplied by @op2, from this value.
	End Rem
	Method SubMul(op1:GMPInt, op2:GMPInt)
		bmx_gmp_mpz_submul(gmpPtr, op1.gmpPtr, op2.gmpPtr)
	End Method
	
	Rem
	bbdoc: Subtracts the result of @op1 multplied by @op2, from this value.
	End Rem
	Method SubMulInt(op1:GMPInt, op2:Int)
		bmx_gmp_mpz_submulint(gmpPtr, op1.gmpPtr, op2)
	End Method
	
	Rem
	bbdoc: Multiplies this value times 2 raised to @op, and returns the result.
	about: This operation can also be defined as a left shift by @op2 bits.
	End Rem
	Method Mul2Exp:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_mul2exp(gmpPtr, op))
	End Method
	
	Rem
	bbdoc: Returns the negative of this value.
	End Rem
	Method Neg:GMPInt()
		Return GMPInt._create(bmx_gmp_mpz_neg(gmpPtr))
	End Method
	
	Rem
	bbdoc: Returns the absolute value.
	End Rem
	Method Absolute:GMPInt()
		Return GMPInt._create(bmx_gmp_mpz_abs(gmpPtr))
	End Method

	Rem
	bbdoc: Divides the value by @d, returning the quotient.
	End Rem
	Method CDivQ:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_q(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: Divides the value by @d, returning the remainder.
	End Rem
	Method CDivR:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_r(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: Divides the value by @d, returning the quotient and setting the remainder in @r.
	End Rem
	Method CDivQR:GMPInt(r:GMPInt, d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_qr(gmpPtr, r.gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: Divides the value by @d, returning the quotient, and the @remainder.
	End Rem
	Method CDivQInt:GMPInt(d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_q_ui(gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: Divides the value by @d, returning the quotient, and the @remainder.
	End Rem
	Method CDivRInt:GMPInt(d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_r_ui(gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: Divides the value by @d, returning the quotient and setting the remainder in @r and @remainder.
	End Rem
	Method CDivQRInt:GMPInt(r:GMPInt, d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_qr_ui(gmpPtr, r.gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: Divides the value by @d, returning the remainder.
	End Rem
	Method CDivInt:Int(d:Int)
		Return bmx_gmp_mpz_cdiv_ui(gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivQ2exp:GMPInt(b:Int)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_q_2exp(gmpPtr, b))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivR2exp:GMPInt(b:Int)
		Return GMPInt._create(bmx_gmp_mpz_cdiv_r_2exp(gmpPtr, b))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQ:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_q(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivR:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_r(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQR:GMPInt(r:GMPInt, d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_qr(gmpPtr, r.gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQInt:GMPInt(d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_q_ui(gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivRInt:GMPInt(d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_r_ui(gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQRInt:GMPInt(r:GMPInt, d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_qr_ui(gmpPtr, r.gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivInt:Int(d:Int)
		Return bmx_gmp_mpz_fdiv_ui(gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQ2exp:GMPInt(b:Int)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_q_2exp(gmpPtr, b))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivR2exp:GMPInt(b:Int)
		Return GMPInt._create(bmx_gmp_mpz_fdiv_r_2exp(gmpPtr, b))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQ:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_q(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivR:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_r(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQR:GMPInt(r:GMPInt, d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_qr(gmpPtr, r.gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQInt:GMPInt(d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_q_ui(gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivRInt:GMPInt(d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_r_ui(gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQRInt:GMPInt(r:GMPInt, d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_qr_ui(gmpPtr, r.gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivInt:Int(d:Int)
		Return bmx_gmp_mpz_tdiv_ui(gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQ2exp:GMPInt(b:Int)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_q_2exp(gmpPtr, b))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivR2exp:GMPInt(b:Int)
		Return GMPInt._create(bmx_gmp_mpz_tdiv_r_2exp(gmpPtr, b))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Modulus:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_mod(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method ModulusInt:GMPInt(d:Int, remainder:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_mod_ui(gmpPtr, d, Varptr remainder))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method DivExact:GMPInt(d:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_divexact(gmpPtr, d.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method DivExactInt:GMPInt(d:Int)
		Return GMPInt._create(bmx_gmp_mpz_divexact_ui(gmpPtr, d))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Divisible:Int(d:GMPInt)
		Return bmx_gmp_mpz_divisible_p(gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method DivisibleInt:Int(d:Int)
		Return bmx_gmp_mpz_divisible_ui_p(gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Divisible2Exp:Int(b:Int)
		Return bmx_gmp_mpz_divisible_2exp_p(gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Congruent:Int(c:GMPInt, d:GMPInt)
		Return bmx_gmp_mpz_congruent_p(gmpPtr, c.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CongruentInt:Int(c:Int, d:Int)
		Return bmx_gmp_mpz_congruent_ui_p(gmpPtr, c, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Congruent2Exp:Int(c:GMPInt, b:Int)
		Return bmx_gmp_mpz_congruent_2exp_p(gmpPtr, c.gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method PowM:GMPInt(_exp:GMPInt, _mod:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_powm(gmpPtr, _exp.gmpPtr, _mod.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method PowMInt:GMPInt(_exp:Int, _mod:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_powm_ui(gmpPtr, _exp, _mod.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Pow:GMPInt(_exp:Int)
		Return GMPInt._create(bmx_gmp_mpz_pow_ui(gmpPtr, _exp))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Function PowInt:GMPInt(base:Int, _exp:Int)
		Return GMPInt._create(bmx_gmp_mpz_ui_pow_ui(base, _exp))
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Method Root:GMPInt(n:Int, result:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_root(gmpPtr, n, Varptr result))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method RootRem:GMPInt(_rem:GMPInt, n:Int)
		Return GMPInt._create(bmx_gmp_mpz_rootrem(gmpPtr, _rem.gmpPtr, n))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Sqrt:GMPInt()
		Return GMPInt._create(bmx_gmp_mpz_sqrt(gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method SqrtRem:GMPInt(rop:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_sqrtrem(gmpPtr, rop.gmpPtr))
	End Method

	Rem
	bbdoc: 
	End Rem
	Method PerfectPower:Int()
		Return bmx_gmp_mpz_perfect_power_p(gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method PerfectSquare:Int()
		Return bmx_gmp_mpz_perfect_square_p(gmpPtr)
	End Method

	Rem
	bbdoc: 
	End Rem
	Method ProbabPrime:Int(reps:Int)
		Return bmx_gmp_mpz_probab_prime_p(gmpPtr, reps)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method NextPrime:GMPInt()
		Return GMPInt._create(bmx_gmp_mpz_nextprime(gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Gcd:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_gcd(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method GcdInt:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_gcd_ui(gmpPtr, op))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method GcdExt:GMPInt(s:GMPint, t:GMPInt, b:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_gcdext(gmpPtr, s.gmpPtr, t.gmpPtr, b.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Lcm:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_lcm(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method LcmInt:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_lcm_ui(gmpPtr, op))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Invert:GMPInt(op:GMPInt, result:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_invert(gmpPtr, op.gmpPtr, Varptr result))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Jacobi:Int(b:GMPInt)
		Return bmx_gmp_mpz_jacobi(gmpPtr, b.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Legendre:Int(p:GMPInt)
		Return bmx_gmp_mpz_legendre(gmpPtr, p.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Kronecker:Int(b:GMPInt)
		Return bmx_gmp_mpz_kronecker(gmpPtr, b.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method KroneckerInt:Int(b:Int)
		Return bmx_gmp_mpz_kronecker_si(gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method IntKronecker:Int(a:Int)
		Return bmx_gmp_mpz_si_kronecker(gmpPtr, a)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Remove:GMPInt(f:GMPInt, count:Int Var)
		Return GMPInt._create(bmx_gmp_mpz_remove(gmpPtr, f.gmpPtr, Varptr count))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Function Fac:GMPInt(op:Int)
		Return GMPInt._create(bmx_gmp_mpz_fac_ui(op))
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Method Bin:GMPInt(k:Int)
		Return GMPInt._create(bmx_gmp_mpz_bin_ui(gmpPtr, k))
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Function BinInt:GMPInt(n:Int, k:Int)
		Return GMPInt._create(bmx_gmp_mpz_bin_uiui(n, k))
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Function Fib:GMPInt(n:Int)
		Return GMPInt._create(bmx_gmp_mpz_fib_ui(n))
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Function Fib2:GMPInt(sub:GMPInt, n:Int)
		Return GMPInt._create(bmx_gmp_mpz_fib2_ui(sub.gmpPtr, n))
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Function LucNum:GMPInt(n:Int)
		Return GMPInt._create(bmx_gmp_mpz_lucnum_ui(n))
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Function LucNum2:GMPInt(sub:GMPInt, n:Int)
		Return GMPInt._create(bmx_gmp_mpz_lucnum2_ui(sub.gmpPtr, n))
	End Function

	Rem
	bbdoc: Compares this value and @op.
	about: Returns a positive value if Self &gt; @op, zero if Self = @op, or a negative value if Self &lt; @op.
	End Rem
	Method Cmp:Int(op:GMPInt)
		Return bmx_gmp_mpz_cmp(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: Compares this value and @op.
	about: Returns a positive value if Self &gt; @op, zero if Self = @op, or a negative value if Self &lt; @op.
	End Rem
	Method CmpD:Int(op:Double)
		Return bmx_gmp_mpz_cmp_d(gmpPtr, op)
	End Method
	
	Rem
	bbdoc: Compares this value and @op.
	about: Returns a positive value if Self &gt; @op, zero if Self = @op, or a negative value if Self &lt; @op.
	End Rem
	Method CpmInt:Int(op:Int)
		Return bmx_gmp_mpz_cmp_si(gmpPtr, op)
	End Method
	
	Rem
	bbdoc: Compare the absolute values of this value and @op.
	about: Returns a positive value if abs(Self) &gt; abs(@op), zero if abs(Self) = abs(@op), or a negative value if abs(Self) &lt; abs(@op).
	End Rem
	Method CmpAbs:Int(op:GMPInt)
		Return bmx_gmp_mpz_cmpabs(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: Compare the absolute values of this value and @op.
	about: Returns a positive value if abs(Self) > abs(@op), zero if abs(Self) = abs(@op), or a negative value if abs(Self) < abs(@op).
	End Rem
	Method CmpAbsD:Int(op:Double)
		Return bmx_gmp_mpz_cmpabs_d(gmpPtr, op)
	End Method
	
	Rem
	bbdoc: Compare the absolute values of this value and @op.
	about: Returns a positive value if abs(Self) > abs(@op), zero if abs(Self) = abs(@op), or a negative value if abs(Self) < abs(@op).
	End Rem
	Method CmpAbsInt:Int(op:Int)
		Return bmx_gmp_mpz_cmpabs_ui(gmpPtr, op)
	End Method
	
	Rem
	bbdoc: Returns +1 if the value &tg; 0, 0 if the value = 0, and -1 if the value &lt; 0
	End Rem
	Method Sign:Int()
		Return bmx_gmp_mpz_sgn(gmpPtr)
	End Method

	Rem
	bbdoc: Returns this value bitwise-and @op.
	End Rem
	Method BitAnd:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_and(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: Returns this value bitwise inclusive-or @op.
	End Rem
	Method BitIor:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_ior(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: Returns this value bitwise exclusive-or @op.
	End Rem
	Method BitXor:GMPInt(op:GMPInt)
		Return GMPInt._create(bmx_gmp_mpz_xor(gmpPtr, op.gmpPtr))
	End Method
	
	Rem
	bbdoc: Returns the one's complement of this value.
	End Rem
	Method BitCom:GMPInt()
		Return GMPInt._create(bmx_gmp_mpz_com(gmpPtr))
	End Method
	
	Rem
	bbdoc: If the value &gt;=0, returns the population count of the value, which is the number of 1 bits in the binary representation.
	about: If the value &lt; 0, the number of 1s is infinite, and the return value is ULONG_MAX, the largest possible int.
	End Rem
	Method PopCount:Int()
		Return bmx_gmp_mpz_popcount(gmpPtr)
	End Method
	
	Rem
	bbdoc: If the value and @op are both &gt;=0 or both &lt;0, returns the hamming distance between the two operands, which is the number of bit positions where the value and @op have different bit values.
	about: If one operand is &gt;=0 and the other &lt;0 then the number of bits different is infinite, and the return value is ULONG_MAX,
	the largest possible unsigned long.
	End Rem
	Method HamDist:Int(op:GMPInt)
		Return bmx_gmp_mpz_hamdist(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: Scans the value, starting from bit @startingBit, towards more significant bits, until the first 0 is found.
	returns: The index of the found bit.
	about: If the bit at @startingBit is already what's sought, then @startingBit is returned.
	<p>
	If there's no bit found, then ULONG_MAX is returned. This will happen past the end of a negative number.
	</p>
	End Rem
	Method Scan0:Int(startingBit:Int)
		Return bmx_gmp_mpz_scan0(gmpPtr, startingBit)
	End Method
	
	Rem
	bbdoc: Scans the value, starting from bit @startingBit, towards more significant bits, until the first 1 is found.
	returns: The index of the found bit.
	about: If the bit at @startingBit is already what's sought, then @startingBit is returned.
	<p>
	If there's no bit found, then ULONG_MAX is returned. This will happen past the end of a nonnegative number.
	</p>
	End Rem
	Method Scan1:Int(startingBit:Int)
		Return bmx_gmp_mpz_scan1(gmpPtr, startingBit)
	End Method
	
	Rem
	bbdoc: Sets bit @bitIndex.
	End Rem
	Method SetBit(bitIndex:Int)
		bmx_gmp_mpz_setbit(gmpPtr, bitIndex)
	End Method
	
	Rem
	bbdoc: Clears bit @bitIndex .
	End Rem
	Method ClrBit(bitIndex:Int)
		bmx_gmp_mpz_clrbit(gmpPtr, bitIndex)
	End Method
	
	Rem
	bbdoc: Complements bit @bitIndex. 
	End Rem
	Method ComBit(bitIndex:Int)
		bmx_gmp_mpz_combit(gmpPtr, bitIndex)
	End Method
	
	Rem
	bbdoc: Tests bit @bitIndex in the value and returns 0 or 1 accordingly.
	End Rem
	Method TstBit:Int(bitIndex:Int)
		Return bmx_gmp_mpz_tstbit(gmpPtr, bitIndex)
	End Method
	
	Rem
	bbdoc: Determines whether the value is odd.
	about: Returns non-zero if yes, zero if no.
	End Rem
	Method Odd:Int()
		Return bmx_gmp_mpz_odd_p(gmpPtr)
	End Method
	
	Rem
	bbdoc: Determines whether the value is even.
	about: Returns non-zero if yes, zero if no.
	End Rem
	Method Even:Int()
		Return bmx_gmp_mpz_even_p(gmpPtr)
	End Method

	Rem
	bbdoc: 
	End Rem
	Method Free()
		If gmpPtr Then
			bmx_gmp_mpz_free(gmpPtr)
			gmpPtr = Null
		End If
	End Method

	Method Delete()
		Free()
	End Method

End Type

Type GMPFloat

	Field gmpPtr:Byte Ptr

End Type

Type GMPRational

	Field gmpPtr:Byte Ptr

End Type
