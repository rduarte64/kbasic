
new_class(pcode___timer, pcode___control, 0); 

new_method(true, pcode___timer, pcode___timer___timer1, pcode___timer);

	 new_param("YesNo", pcode__BOOLEAN, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_MouseTracking, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_MouseTracking, pcode__BOOLEAN);



new_method(true, pcode___timer, pcode___timer__EVENT_OnSingleShot, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnEnabled, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnDisabled, pcode__VOID, false, false, false, true);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_CursorAnimation, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_CursorAnimation, pcode__QString);

new_method(true, pcode___timer, pcode___timer__METHOD_DataIds, pcode___strings);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataRemove, pcode__VOID);
	 
new_method(true, pcode___timer, pcode___timer__METHOD_DataRemoveAll, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__BOOLEAN, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataSetBoolean, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__INTEGER, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataSetInteger, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataSetString, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__DOUBLE, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataSetDouble, pcode__VOID);


	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__LONG, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataSetLong, pcode__VOID);
	 
   new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__CURRENCY, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataSetDecimal, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__DATE, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataSetDateTime, pcode__VOID);
	

	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataBoolean, pcode__BOOLEAN);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataInteger, pcode__INTEGER);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataString, pcode__QString);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataDouble, pcode__DOUBLE);
	  
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataLong, pcode__LONG);

	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataDecimal, pcode__CURRENCY);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__METHOD_DataDateTime, pcode__DATE);
	 

new_method(true, pcode___timer, pcode___timer__METHOD_ClearFocus, pcode__VOID);

new_method(true, pcode___timer, pcode___timer__METHOD_ToggleVisible, pcode__VOID);

	 new_param("Milliseconds", pcode__INTEGER, false);
new_method(true, pcode___timer, pcode___timer__METHOD_SingleShot, pcode__VOID);
	 
new_method(true, pcode___timer, pcode___timer__METHOD_StartTimer, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_StopTimer, pcode__VOID);
	 
	 new_param("LocalX", pcode__INTEGER, false);
new_method(true, pcode___timer, pcode___timer__METHOD_GlobalX, pcode__INTEGER);
	 
	 new_param("LocalY", pcode__INTEGER, false);
new_method(true, pcode___timer, pcode___timer__METHOD_GlobalY, pcode__INTEGER);	 

	 new_param("GlobalX", pcode__INTEGER, false);
new_method(true, pcode___timer, pcode___timer__METHOD_LocalX, pcode__INTEGER);
	 
	 new_param("GlobalY", pcode__INTEGER, false);
new_method(true, pcode___timer, pcode___timer__METHOD_LocalY, pcode__INTEGER);
	 
new_method(true, pcode___timer, pcode___timer__METHOD_UnderMouse, pcode__BOOLEAN);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Mask, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Mask, pcode__QString);

   new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_SoundOnEvent, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_SoundOnEvent, pcode__QString);

   new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Left, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Left, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Top, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Top, pcode__t_integer);

   new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_LocalX, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_LocalX, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_LocalY, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_LocalY, pcode__t_integer);

	 new_param("n", pcode__BOOLEAN, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_DrawOnPaint, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_DrawOnPaint, pcode__BOOLEAN);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Palette, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Palette, pcode__QString);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_BackgroundStyle, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_BackgroundStyle, pcode__QString);



    new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Layout, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Layout, pcode__QString);

	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_EventOnOpen, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_EventOnOpen, pcode__t_boolean);

	 new_param("f", pcode___form, false);
new_method(true, pcode___timer, pcode___timer___timer, pcode___timer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Interval, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Interval, pcode__t_integer);
new_method(true, pcode___timer, pcode___timer__METHOD_IsRunning, pcode__t_boolean);
new_method(true, pcode___timer, pcode___timer__METHOD_Start, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Stop, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__EVENT_OnEvent, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__METHOD_Move, pcode__VOID);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__METHOD_Resize, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Show, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Hide, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_RepaintAlways, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Repaint, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Raise, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Lower, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Close, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_Open, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__METHOD_SetFocus, pcode__VOID);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Name, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Name, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Group, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Group, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Background, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Background, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_X, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_X, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Y, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Y, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Width, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Width, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Height, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Height, pcode__t_integer);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_GlobalX, pcode__t_integer);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_GlobalY, pcode__t_integer);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_OldX, pcode__t_integer);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_OldY, pcode__t_integer);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_OldWidth, pcode__t_integer);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_OldHeight, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_MinimumWidth, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_MinimumWidth, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_MinimumHeight, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_MinimumHeight, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_MaximumWidth, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_MaximumWidth, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_MaximumHeight, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_MaximumHeight, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Tag, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Tag, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_CSV, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_CSV, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_ParentForm, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_ParentForm, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_ParentControl, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_ParentControl, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_DragDrop, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__GETPROPERTY_ParentControl1, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_ControlType, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_ControlType, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Focus, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Focus, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FocusPolicy, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FocusPolicy, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FocusProxy, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FocusProxy, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FocusOrder, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FocusOrder, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Cursor, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Cursor, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FontName, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FontName, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FontSize, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FontSize, pcode__t_integer);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FontItalic, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FontItalic, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FontBold, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FontBold, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FontUnderline, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FontUnderline, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_FontColor, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_FontColor, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Enabled, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Enabled, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Visible, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Visible, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_StatusTip, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_StatusTip, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_ToolTip, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_ToolTip, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_StyleSheet, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_StyleSheet, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_WhatsThis, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_WhatsThis, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_TimerInterval, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_TimerInterval, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_Opacity, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_Opacity, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_BoxIndex, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_BoxIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_SplitIndex, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_SplitIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_TabIndex, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_TabIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_BoxX, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_BoxX, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_BoxY, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_BoxY, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_ParentIndex, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_ParentIndex, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__SETPROPERTY_ControlType1, pcode__VOID);
new_method(true, pcode___timer, pcode___timer__GETPROPERTY_ControlType1, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_SQLName, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_SQLName, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_SQLType, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_SQLType, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_SQLCaption, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_SQLCaption, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___timer, pcode___timer__SETPROPERTY_SQLWidth, pcode__VOID);
new_property_get(pcode___timer, pcode___timer__GETPROPERTY_SQLWidth, pcode__t_integer);
new_method(true, pcode___timer, pcode___timer__EVENT_OnOpen, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__BOOLEAN_POINTER, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnClose, pcode__VOID, false, false, false, true);
/*
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnContextMenu, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__t_boolean, false);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnDragEnter, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnDragExit, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__t_boolean, false);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnDragMove, pcode__VOID, false, false, false, true);
*/
	 new_param("Cancel", pcode__t_boolean, false);
	 new_param("MimeData", pcode__QString, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnDrop, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnEnter, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnGotFocus, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnLostFocus, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnHide, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnKeyDown, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnKeyUp, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnKeyPress, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnExit, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnDblClick, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnClick, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnMouseMove, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnMouseDown, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnMouseUp, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("OldX", pcode__t_integer, false);
	 new_param("OldY", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnMove, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnPaint, pcode__VOID, false, false, false, true);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("OldWidth", pcode__t_integer, false);
	 new_param("OldHeight", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnResize, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnShow, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___timer, pcode___timer__EVENT_OnMouseWheel, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnTimer, pcode__VOID, false, false, false, true);
new_method(true, pcode___timer, pcode___timer__EVENT_OnPrint, pcode__VOID, false, false, false, true);
