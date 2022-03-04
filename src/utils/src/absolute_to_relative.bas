Sub sanitizeSlashes (ByRef spec As String)
	Dim As Integer i
	For i = 1 To Len (spec)
		If Mid (spec, i, 1) = Chr (92) Then Mid (spec, i, 1) = "/"
	Next
End Sub

Function absoluteToRelative (fileSpec As String, refSpec As String) As String
	Dim As Integer i
	Dim As Integer fi
	Dim As Integer numBacks
	Dim As String res

	sanitizeSlashes fileSpec
	sanitizeSlashes refSpec

	' Check how much of fileSpec and refSpec are the same
	For i = 1 To Len (fileSpec)
		If i > Len (refSpec) Then Exit For
		If Mid (fileSpec, i, 1) <> Mid (refSpec, i, 1) Then Exit For
	Next i

	fi = i

	If fi > Len (refSpec) Then
		' fileSpec contains refSpec, so numBacks = 0
		numBacks = 0
	Else
		' Count how many /s there are, then add 1
		numBacks = 1
		For i = fi To Len (refSpec)
			If Mid (refSpec, i, 1) = "/" Then numBacks = numBacks + 1
		Next i
	End If

	res = ""
	For i = 1 To numBacks
		res = res & "../"
	Next i

	res = res & Right (fileSpec, Len (fileSpec) - fi + 1)

	Return res
End Function

Print absoluteToRelative (Command (1), Curdir)

' Ref = 'c:\a\b\'
' Abs = 'c:\a\c\d\e.pel'
'       ..\c\d\e.pel

 'Ref = 'c:\a\b\'
 'Abs = 'c:\a\e.pel'
'       ..\e.pel'