SuperStrict

Framework BaH.qrencode
Import BRL.GLMax2D


Local code:TQRCode = TQRCode.encodeString("Привет!")

Local pix:TPixmap = code.getPixmap(8)

Graphics 800, 600, 0

SetClsColor 255, 255, 255
SetColor 0, 0, 0

Local image:TImage = LoadImage(pix)

While Not KeyDown(KEY_ESCAPE)

	Cls

	DrawImage image, 100, 100

	Flip
Wend