' Simple GUI by Lothar Schirm - https://www.freebasic-portal.de/projekte/simple-gui-98.html

'===============================================================================
' GUI.bas
' Simple GUI for the FB graphics window, color depth 32 bit, char size 8x16
' First release Jan 17, 2015
' Last update Jan 19, 2015 (Sub EditText)
'===============================================================================

#include "gui.bi"

Sub OpenWindow (w As Integer, h As Integer, title As String)
'Window, textcolor black, backcolor white, 2 pages, char size 8x16

	Screenres w, h, 32, 3
	Windowtitle title
	Width w \ 8, h \ 16
	'Color black, white
	Color black, RGB (127,127,127)
	Cls 0

End Sub


Function Window_Event_Close() As Integer
'Returns 1 if the "Close" button ("x") of the window was clicked

	If Inkey = Chr(255, 107) Then Return 1 Else Return 0

End Function 


Sub Button_Draw(btn As Button, colour As UInteger)
'Draw a button - used by Subs "Button_New" and "Button_Event"

	Dim As Integer TextW, TextH

	Line (btn.x, btn.y) - (btn.x + btn.w, btn.y + btn.h), white, BF
	Line (btn.x, btn.y) - (btn.x + btn.w, btn.y + btn.h), colour, B
	TextW = 8 * Len(btn.text)
	TextH = 16
	Draw String (btn.x + 0.5 * (btn.w - TextW), btn.y + 0.5 * (btn.h - TextH)), _
								btn.text, colour

End Sub


Function Button_New (	x As Integer, y As Integer, w As Integer, h As Integer, _
						Text As String) As Button
'Defines and draws a new button

	Dim As Button btn

	btn.x = x
	btn.y = y
	btn.h = h
	btn.w = w
	btn.text = text

	Button_Draw(btn, Color)

	Return btn

End Function


Function Button_Event(btn As Button) As Integer
'Returns 1 when button was clicked

	Dim As Integer mx, my, mbtn
	Dim As UInteger colour

	Getmouse(mx, my,, mbtn)

	If (mx >= btn.x) And (mx <= btn.x + btn.w) And (my >= btn.y) And (my <= btn.y + btn.h) _
		And mbtn = 1 Then
		'Active state of button (red):
		colour = Color
		Button_Draw(btn, red)
		'Wait until mouse button is released:
		Do
			Getmouse(mx, my,, mbtn)
		Loop Until mbtn = 0
		'Inactive state of button:
		Button_Draw(btn, Color)
		Return 1
	Else
		Return 0
	End if

End Function


Sub SetText (	x As Integer, y As Integer, w As Integer, h As Integer, text As String, _
				colour As UInteger = Color, bg As UInteger = white)
'Sets a text left justified into a rectangular area. If the text is too long, it
'will be truncated. This Sub is used by the following controls.

	Line (x + 1, y + 1) - (x + w - 2, y + h - 2), bg, BF
	Draw String (x + 4, y + 0.5 * (h - 16)), Left(text, w / 8 - 1), colour

End Sub

Sub EditText (	x As Integer, y As Integer, w As Integer, h As Integer, _
				ByRef text As String, ReadOnly As Integer = 0)
'Edits the text within a rectangular aerea.
'ReadOnly = 1: Text cannot be edited, can only be scrolled.
'The Sub is used by the following controls.

	Dim As String	strKey
	Dim As Integer ascKey, CPos, Offset, MaxLen, mx, my, mb

	MaxLen = w \ 8 - 1
	CPos = Len(text)
	If Len(text) > MaxLen Then Offset = Len(text) - MaxLen Else Offset = 0

	Do

	'Display text with cursor:
	ScreenLock
	SetText(x, y, w, h, Mid(text, Offset + 1, MaxLen))
	Draw String (x + 4 + 8 * (CPos - Offset), y + 0.5 * (h - 16)), "_", red
	ScreenUnlock

	'Return key:
	strKey = Inkey
		ascKey = Asc(strKey)

		If strKey <> "" Then
			ascKey = Asc(strKey)

			If ascKey = 255 Then

				ascKey = Asc(Right(strKey, 1))
				Select Case ascKey
					Case 75
						'Move cursor left:
						If CPos > 0 Then
							CPos = CPos - 1
							If CPos < Offset Then Offset = Offset - 1
						End If
					Case 77
						'Move cursor right:
						If CPos < Len(text) Then
							CPos = CPos + 1
							If CPos > MaxLen - 1 + Offset Then Offset = Offset + 1
						End If
					Case 71
						'Move Cursor to the beginning
						CPos = 0
						Offset = 0
					Case 79
						'Move Cursor to the end
						CPos = Len(text)
						If Len(Text) > MaxLen Then Offset = Len(text) - MaxLen
					Case 83
						If ReadOnly = 0 Then
							'Del
							If (Len(text) > 0) And (CPos < Len(text)) Then _
								text = Left(text, CPos) + Right(text, Len(text) - CPos - 1)
						End If
				End Select

			Else

				Select Case ascKey
					Case 8
						If ReadOnly = 0 Then
							'Backspace:
							If (Len(text) > 0) And (CPos > 0) Then
								text = Left(text, CPos - 1) + Right(text, (Len(text) - CPos))
								CPos = CPos - 1
								If Offset > 0 Then Offset = Offset - 1
							End If
						End If
					Case 32 To 255
						If ReadOnly = 0 Then
							'Printable characters:
							text = Left(text, CPos) + Chr(asckey) + Right(text, Len(text) - CPos)
							CPos = CPos + 1
							If CPos > MaxLen - 1 + Offset Then Offset = Offset + 1
						End If
				End Select

			End If

		End If

		GetMouse mx,my,,mb

	Loop Until ascKey = 13 Or ascKey = 9 Or ascKey = 27 _
		Or (mb = 1 And (mx < x Or mx > (x + w) Or my < y Or my > (y + h)))

	'End:
	Screenlock
	SetText(x, y, w, h, text)
	Screenunlock

End Sub


Function Label_New (	x As Integer, y As Integer, w As Integer, h As Integer, _
						text As String, fg As uInteger = Color, bg As uInteger = white) As Label
'Define and draw a new label

	Dim As Label lbl

	SetText x, y, w, h, text, fg, bg

	lbl.x = x
	lbl.y = y
	lbl.h = h
	lbl.w = w
	lbl.text = text

	Return lbl

 End Function


Function TextBox_New (	x As Integer, y As Integer, w As Integer, h As Integer, _
						text As String) As TextBox
'Define and draw a new textbox:

	Dim As TextBox tb

	Line (x, y) - (x + w, y + h),, B
	SetText(x, y, w, h, text)

	tb.x = x
	tb.y = y
	tb.h = h
	tb.w = w
	tb.text = text

	Return tb

End Function


Sub TextBox_SetText(ByRef tb As TextBox, text As String)
'Set a text into a textbox

	SetText(tb.x, tb.y, tb.w, tb.h, text)
	tb.text = text

End Sub


Function TextBox_GetText(tb As Textbox) As String
'Get text from textbox

	Return tb.text

End Function


Sub TextBox_Edit(ByRef tb As Textbox, ReadOnly As Integer = 0)
'Edit text in textbox

	EditText(tb.x, tb.y, tb.w, tb.h, tb.text, ReadOnly)

End Sub


Function TextBox_Event(tb As TextBox) As Integer
'Returns 1 when textbox was clicked

	Dim As Integer mx, my, mbtn

	Getmouse(mx, my,, mbtn)

	If (mx >= tb.x) And (mx <= tb.x + tb.w) And (my >= tb.y) And (my <= tb.y + tb.h) _
		And mbtn = 1 Then
		Do
			Getmouse(mx, my,, mbtn)
		Loop Until mbtn = 0
		Return 1
	Else
		Return 0
	End If

End Function


Function ListBox_New(x As Integer, y As Integer, w As Integer, h As Integer) As ListBox
'Draw and define new ListBox

	Dim As ListBox lb
	Dim As Integer i

	Line (x, y) - (x + w, y + h),,B

	lb.x = x
	lb.y = y
	lb.w = w
	lb.h = h
	For i = 0 To 1e4
		lb.buffer(i) = ""
	Next
	lb.imax = -1
	lb.offset = 0
	lb.nmax = h \ 16
	lb.index = -1

	Return lb

End Function


Sub DisplayItems(lb As ListBox)
'Display items in the listbox (used for vertical scrolling)
'This Sub is used by the ListBox.

	Dim As Integer i

	For i = 0 To lb.nmax - 1
		SetText(lb.x, lb.y + 16 * i, lb.w, 16, lb.buffer(i + lb.offset))
	Next

End Sub


Sub ListBox_Add(ByRef lb As ListBox, item As String)
'Add an item

	If lb.imax < 1e4 Then
		lb.imax = lb.imax + 1
		If lb.imax - lb.offset > lb.nmax - 1 Then lb.offset = lb.offset + 1
		lb.buffer(lb.imax) = item
		DisplayItems(lb)
	End If

End Sub


Function ListBox_GetMaxIndex(lb As ListBox) As Integer
'Returns the maximum index of items in the listbox

	Return lb.imax

End Function


Sub ListBox_SetItem(ByRef lb As Listbox, index As Integer, item As String)
'Set text of an existing item

	If index <= lb.imax Then
		DisplayItems(lb)
		lb.buffer(index) = item
	End If

End Sub


Sub ListBox_Clear(ByRef lb As ListBox)
'Delete all items in a textbox

	Dim As Integer i

	For i = 0 To lb.imax
		lb.buffer(i) = ""
	Next
	lb.imax = -1
	lb.offset = 0
	DisplayItems(lb)

End Sub


Function ListBox_GetIndex(lb As ListBox) As Integer
'Returns the selected index

	Return lb.index

End Function


Function ListBox_GetItem(lb As ListBox, index As Integer) As String
'Returns item text at index

	If index >= 0 Then Return lb.buffer(index) Else Return ""

End Function


Function ListBox_Event(ByRef lb As ListBox) As Integer
'Returns 1 when listbox was clicked or the mousewheel was moved with mouse position
'within the listbox. If listbox was clicked, the selected index is stored. If mousewheel
'was moved, the items in the listbox are scrolled vertical.

	Dim As Integer i, index, mx, my, mb, event, mw0
	Static As Integer mw

	mw0 = mw
	Getmouse(mx, my, mw, mb)

	If (mx >= lb.x) And (mx <= lb.x + lb.w) And (my >= lb.y) And (my <= lb.y + lb.h) Then

		If mb = 1 Then
			'Left mousebutton:
			i = (my - lb.y) \ 16 + lb.offset
			'Active state of item (red):
			SetText(lb.x, lb.y + 16 * (i - lb.offset), lb.w, 16, lb.buffer(i), red)
			'Wait until mouse button is released:
			Do
				Getmouse(mx, my,, mb)
			Loop Until mb = 0
			'Inactive state of item:
			SetText(lb.x, lb.y + 16 * (i - lb.offset), lb.w, 16, lb.buffer(i))
			lb.index = i
			event = 1
		End If

		IF (mw - mw0 > 0) And lb.offset > 0 Then
			'Mousewheel:
			lb.offset = lb.offset - 1
			DisplayItems(lb)
			event = 1
		ElseIF (mw - mw0) < 0 And (lb.imax - lb.offset) >= lb.nmax Then
			lb.offset = lb.offset + 1
			DisplayItems(lb)
			event = 1
		End If

	Else
		event = 0
	End If

	Return event

End Function


Function DataGrid_New (	x As Integer, y As Integer, m As Integer, n As Integer, _
						cw() As Integer) As DataGrid
'Draw and define new datagrid.
'x, y: position left top
'm, n: maximum indexes of rows and columns
'cw(): columnwidths

	Dim As DataGrid dg
	Dim As Integer i, j, k = Ubound(cw)

	'Define all parameters:
	dg.x = x
	dg.y = y
	dg.m = m
	dg.n = n
	dg.colwidth(0) = cw(0)
	dg.colpos(0) = dg.x
	For j = 1 To k
		dg.colwidth(j) = cw(j)
		dg.colpos(j) = dg.colpos(j - 1) + dg.colwidth(j - 1)
	Next
	For i = 0 To 100
		For j = 0 To 100
			dg.buffer(i, j) = ""
		Next
	Next
	dg.index_row = -1
	dg.index_col = - 1
	dg.w = dg.colpos(k) + dg.colwidth(k) - dg.x
	dg.h = 20 * (m + 1)

	'Draw Data grid:
	Line (dg.x, dg.y) - (dg.x + dg.w, dg.y + dg.h), black, B
	For i = 1 To m
		Line (dg.x, dg.y + i * 20) - (dg.x + dg.w, dg.y + i * 20), cyan
	Next
	For j = 1 To n
		Line (dg.colpos(j), dg.y) - (dg.colpos(j), dg.y + dg.h), cyan
	Next

	Return dg

End Function


Sub DataGrid_SetItem(ByRef dg As DataGrid, i As Integer, j As Integer, _
											item As String)
'Set an item into the data grid, row i, column j

	If i <= dg.m And j <= dg.n Then
		SetText(dg.colpos(j), dg.y + 20 * i, dg.colwidth(j), 20, item)
		dg.buffer(i, j) = item
	End If

End Sub


Sub DataGrid_Clear(ByRef dg As DataGrid)
'Delete all items of data grid

	Dim As Integer i, j

	For i = 0 To 100
		For j = 0 To 100
			DataGrid_SetItem(dg, i, j, "")
		Next
	Next

End Sub


Sub DataGrid_GetIndexes(dg As DataGrid, ByRef i As Integer, ByRef j As Integer)
'Returns selected indexes of data grid

	i = dg.index_row
	j = dg.index_col

End Sub


Function DataGrid_GetItem(dg As DataGrid, i As Integer, j As Integer) As String
'Returns item at row i, column j

	Return dg.buffer(i, j)

End Function


Sub DataGrid_EditItem(ByRef dg As DataGrid, i As Integer, j As Integer, _
											ReadOnly As Integer = 0)
'Edit item at row i, column j

	If i <= dg.m And j <= dg.n Then _
		EditText(dg.colpos(j), dg.y + 20 * i, dg.colwidth(j), 20, dg.buffer(i, j),_
							ReadOnly)

End Sub


Function DataGrid_Event(ByRef dg As DataGrid) As Integer
'Returns 1 if data grid is clicked and stores indexes of selected item

	Dim As Integer i, j, mx, my, mb, event
	Dim As String text

	Getmouse(mx, my,, mb)

	If (mx >= dg.x) And (mx <= dg.x + dg.w) And (my >= dg.y) And (my <= dg.y + dg.h) _
		And mb = 1 Then
		i = (my - dg.y) \ 20
		For j = 0 To dg.n
			If dg.colpos(j) > mx Then Exit For
		Next
		j = j - 1
		'Active state of item (red):
		SetText(dg.colpos(j), dg.y + 20 * i, dg.colwidth(j), 20, dg.buffer(i, j), red)
		'Wait until mouse button is released:
		Do
			Getmouse(mx, my,, mb)
		Loop Until mb = 0
		'Active state of item :
		SetText(dg.colpos(j), dg.y + 20 * i, dg.colwidth(j), 20, dg.buffer(i, j))
		dg.index_row = i
		dg.index_col = j
		event = 1
	Else
		event = 0
	End if

	Return event

End Function
