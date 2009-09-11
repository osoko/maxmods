SuperStrict


Rem
bbdoc: 
End Rem
Module BaH.GMP

?macos
ModuleInfo "LD_OPTS: -L%PWD%/lib/macos"
?win32
ModuleInfo "LD_OPTS: -L%PWD%/lib/win32"
?linux
?

Import "common.bmx"


Rem
bbdoc: 
End Rem
Type GMPInt

	Field gmpPtr:Byte Ptr

	Rem
	bbdoc: 
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
	bbdoc: Adds @op1 to @op2, setting the result here.
	End Rem
	Method Add(op1:GMPInt, op2:GMPInt)
		bmx_gmp_mpz_add(gmpPtr, op1.gmpPtr, op2.gmpPtr)
	End Method
	
	Rem
	bbdoc: Adds @op1 to @op2, setting the result here.
	End Rem
	Method AddInt(op1:GMPInt, op2:Int)
		bmx_gmp_mpz_addint(gmpPtr, op1.gmpPtr, op2)
	End Method
	
	Rem
	bbdoc: Subtracts @op2 from @op1, setting the result here.
	End Rem
	Method Sub(op1:GMPInt, op2:GMPInt)
		bmx_gmp_mpz_sub(gmpPtr, op1.gmpPtr, op2.gmpPtr)
	End Method
	
	Rem
	bbdoc: Subtracts @op2 from @op1, setting the result here.
	End Rem
	Method SubInt(op1:GMPInt, op2:Int)
		bmx_gmp_mpz_subint(gmpPtr, op1.gmpPtr, op2)
	End Method
	
	Rem
	bbdoc: Subtracts @op2 from @op1, setting the result here.
	End Rem
	Method IntSub(op1:Int, op2:GMPInt)
		bmx_gmp_mpz_intsub(gmpPtr, op1, op2.gmpPtr)
	End Method
	
	Rem
	bbdoc: Multiplies @op1 by @op2, setting the result here.
	End Rem
	Method Mul(op1:GMPInt, op2:GMPInt)
		bmx_gmp_mpz_mul(gmpPtr, op1.gmpPtr, op2.gmpPtr)
	End Method
	
	Rem
	bbdoc: Multiplies @op1 by @op2, setting the result here.
	End Rem
	Method MulInt(op1:GMPInt, op2:Int)
		bmx_gmp_mpz_mulint(gmpPtr, op1.gmpPtr, op2)
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
	bbdoc: Multiplies @op1 times 2 raised to @op2, and sets the result here.
	about: This operation can also be defined as a left shift by @op2 bits.
	End Rem
	Method Mul2Exp(op1:GMPInt, op2:Int)
		bmx_gmp_mpz_mul2exp(gmpPtr, op1.gmpPtr, op2)
	End Method
	
	Rem
	bbdoc: Negates @op and sets here.
	End Rem
	Method Neg(op:GMPInt)
		bmx_gmp_mpz_neg(gmpPtr, op.gmpPtr)
	End Method
	
	Rem
	bbdoc: Sets this value as the absolute value of @op.
	End Rem
	Method Absolute(op:GMPInt)
		bmx_gmp_mpz_abs(gmpPtr, op.gmpPtr)
	End Method

	Rem
	bbdoc: 
	End Rem
	Method CDivQ(n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_cdiv_q(gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivR(n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_cdiv_r(gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivQR(r:GMPInt, n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_cdiv_qr(gmpPtr, r.gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivQInt:Int(n:GMPInt, d:Int)
		Return bmx_gmp_mpz_cdiv_q_ui(gmpPtr, n.gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivRInt:Int(n:GMPInt, d:Int)
		Return bmx_gmp_mpz_cdiv_r_ui(gmpPtr, n.gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivQRInt:Int(r:GMPInt, n:GMPInt, d:Int)
		Return bmx_gmp_mpz_cdiv_qr_ui(gmpPtr, r.gmpPtr, n.gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivInt:Int(d:Int)
		Return bmx_gmp_mpz_cdiv_ui(gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivQ2exp(n:GMPInt, b:Int)
		bmx_gmp_mpz_cdiv_q_2exp(gmpPtr, n.gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CDivR2exp(n:GMPInt, b:Int)
		bmx_gmp_mpz_cdiv_r_2exp(gmpPtr, n.gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQ(n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_fdiv_q(gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivR(n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_fdiv_r(gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQR(r:GMPInt, n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_fdiv_qr(gmpPtr, r.gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQInt:Int(n:GMPInt, d:Int)
		Return bmx_gmp_mpz_fdiv_q_ui(gmpPtr, n.gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivRInt:Int(n:GMPInt, d:Int)
		Return bmx_gmp_mpz_fdiv_r_ui(gmpPtr, n.gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivQRInt:Int(r:GMPInt, n:GMPInt, d:Int)
		Return bmx_gmp_mpz_fdiv_qr_ui(gmpPtr, r.gmpPtr, n.gmpPtr, d)
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
	Method FDivQ2exp(n:GMPInt, b:Int)
		bmx_gmp_mpz_fdiv_q_2exp(gmpPtr, n.gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method FDivR2exp(n:GMPInt, b:Int)
		bmx_gmp_mpz_fdiv_r_2exp(gmpPtr, n.gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQ(n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_tdiv_q(gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivR(n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_tdiv_r(gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQR(r:GMPInt, n:GMPInt, d:GMPInt)
		bmx_gmp_mpz_tdiv_qr(gmpPtr, r.gmpPtr, n.gmpPtr, d.gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQInt:Int(n:GMPInt, d:Int)
		Return bmx_gmp_mpz_tdiv_q_ui(gmpPtr, n.gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivRInt:Int(n:GMPInt, d:Int)
		Return bmx_gmp_mpz_tdiv_r_ui(gmpPtr, n.gmpPtr, d)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivQRInt:Int(r:GMPInt, n:GMPInt, d:Int)
		Return bmx_gmp_mpz_tdiv_qr_ui(gmpPtr, r.gmpPtr, n.gmpPtr, d)
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
	Method TDivQ2exp(n:GMPInt, b:Int)
		bmx_gmp_mpz_tdiv_q_2exp(gmpPtr, n.gmpPtr, b)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method TDivR2exp(n:GMPInt, b:Int)
		bmx_gmp_mpz_tdiv_r_2exp(gmpPtr, n.gmpPtr, b)
	End Method
	
	Method Modulus(n:GMPInt, d:GMPInt)
	' TODO
	End Method
	
	Method ModulusInt:Int(n:GMPInt, d:Int)
	' TODO
	End Method
	
	Method DivExact(n:GMPInt, d:GMPInt)
	' TODO
	End Method
	
	Method DivExactInt(n:GMPInt, d:Int)
	' TODO
	End Method
	
	Method Divisible:Int(d:GMPInt)
	' TODO
	End Method
	
	Method DivisibleInt:Int(d:Int)
	' TODO
	End Method
	
	Method Divisible2Exp:Int(b:Int)
	' TODO
	End Method
	
	Method Congruent:Int(c:GMPInt, d:GMPInt)
	' TODO
	End Method
	
	Method CongruentInt:Int(c:Int, d:Int)
	' TODO
	End Method
	
	Method Congruent2Exp:Int(c:GMPInt, b:Int)
	' TODO
	End Method
	
	Method PowM(base:GMPInt, _exp:GMPInt, _mod:GMPInt)
	' TODO
	End Method
	
	Method PowMInt(base:GMPInt, _exp:Int, _mod:GMPInt)
	' TODO
	End Method
	
	Method Pow(base:GMPInt, _exp:Int)
	' TODO
	End Method
	
	Method PowInt(base:Int, _exp:Int)
	' TODO
	End Method
	
	Method Root:Int(op:GMPInt, n:Int)
	' TODO
	End Method
	
	Method RootRem(_rem:GMPInt, u:GMPInt, n:Int)
	' TODO
	End Method
	
	Method Sqrt(op:GMPInt)
	' TODO
	End Method
	
	Method SqrtRem(rop:GMPInt, op:GMPInt)
	' TODO
	End Method
	
	Method PerfectPower:Int()
	' TODO
	End Method
	
	Method PerfectSquare:Int()
	' TODO
	End Method
	
	Method ProbabPrime:Int(reps:Int)
	' TODO
	End Method
	
	Method NextPrime(op:GMPInt)
	' TODO
	End Method
	
	Method Gcd(op1:GMPInt, op2:GMPInt)
	' TODO
	End Method
	
	Method GcdExt(s:GMPint, t:GMPInt, a:GMPInt, b:GMPInt)
	' TODO
	End Method
	
	Method Lcm(op1:GMPInt, op2:GMPInt)
	' TODO
	End Method
	
	Method LcmInt(op1:GMPInt, op2:Int)
	' TODO
	End Method
	
	Method Invert:Int(op1:GMPInt, op2:GMPInt)
	' TODO
	End Method
	
	Method Jacobi:Int(b:GMPInt)
	' TODO
	End Method
	
	Method Legendre:Int(p:GMPInt)
	' TODO
	End Method
	
	Method Kronecker:Int(b:GMPInt)
	' TODO
	End Method
	
	Method KroneckerInt:Int(b:Int)
	' TODO
	End Method
	
	Method IntKronecker:Int(a:Int)
	' TODO
	End Method
	
	Method Remove:Int(op:GMPInt, f:GMPInt)
	' TODO
	End Method
	
	Method Fac(op:Int)
	' TODO
	End Method
	
	Method Bin(n:GMPInt, k:Int)
	' TODO
	End Method
	
	Method BinInt(n:Int, k:Int)
	' TODO
	End Method
	
	Method Fib(n:Int)
	' TODO
	End Method
	
	Method Fib2(fnsub1:GMPInt, n:Int)
	' TODO
	End Method
	
	Method LucNum(n:Int)
	' TODO
	End Method
	
	Method LucNum2(lnsub1:GMPInt, n:Int)
	' TODO
	End Method
	
	Method Cmp:Int(op:GMPInt)
	' TODO
	End Method
	
	Method CmpD:Int(op:Double)
	' TODO
	End Method
	
	Method CpmInt:Int(op:Int)
	' TODO
	End Method
	
	Method CmpAbs:Int(op:GMPInt)
	' TODO
	End Method
	
	Method CmpAbsD:Int(op:Double)
	' TODO
	End Method
	
	Method CmpAbsInt:Int(op:Int)
	' TODO
	End Method
	
	Method Sign:Int()
	' TODO
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
