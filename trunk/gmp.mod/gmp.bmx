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
	bbdoc: 
	End Rem
	Method GetDouble:Double()
		Return bmx_gmp_mpz_getdouble(gmpPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method GetDouble2Exp:Double(_exp:Int Var)
		Return bmx_gmp_mpz_getdouble2exp(gmpPtr, Varptr _exp)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method GetStr:String(base:Int = 10)
		Return bmx_gmp_mpz_getstr(gmpPtr, base)
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
