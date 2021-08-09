#!/usr/bin/env python
# -*- coding: utf-8 -*-
#使用中文必需加入編碼方式,預設ASCII

#import os, sys

import pygtk
pygtk.require('2.0')
import gtk
import os
import shutil
import gobject

#叫出設定檔並存成串列
home_path = os.environ['HOME']
#判斷家目錄.oxim/下oxim.conf是否存在
if not os.path.exists('%s/.oxim/oxim.conf'%home_path):
    #不存在則複製一個
    shutil.copyfile('/etc/oxim/oxim.conf','%s/.oxim/oxim.conf'%home_path)
input = open('%s/.oxim/oxim.conf'%home_path ,'r')
conf_file = input.read()
input.close()

#輸入法的Liststore資料,5個欄位
(
    COLUMN_CHANGE,
    COLUMN_DEFAULT,
    COLUMN_NAME,
    COLUMN_SHORTCUTS,
    COLUMN_BUILT,
    COLUMN_EN,
    COLUMN_CH,
    COLUMN_ALIAS,
    COLUMN_KEY
) = range(9)

#宣告data 給model 使用
data = [] 

class oximsetup(gtk.Window):
    
    def setconf(self,widget): #確定後將conf_file寫入oxim.conf
	global conf_file #廣域變數宣告,用於區域
	output = open('%s/.oxim/oxim.conf'%home_path ,'w')
	output.write(conf_file)
	output.close()
	#程式未完成暫不使用
	#os.system('oxim-agent -r') #重新啓動OXIM引擎
	#gtk.main_quit()	#離開oxim-setup-pygtk

    def __create_model(self):#建立資料模組
        lstore = gtk.ListStore(
            gobject.TYPE_BOOLEAN,
            gobject.TYPE_STRING,
            gobject.TYPE_STRING,
            gobject.TYPE_STRING,
            gobject.TYPE_STRING,
            gobject.TYPE_STRING,
            gobject.TYPE_STRING,
            gobject.TYPE_STRING,
            gobject.TYPE_STRING)
	
        for item in data:#一筆一筆給入資料
            iter = lstore.append()#加入liststore
            lstore.set(iter,
                COLUMN_CHANGE, item[COLUMN_CHANGE],
                COLUMN_NAME, item[COLUMN_NAME],
                COLUMN_SHORTCUTS, item[COLUMN_SHORTCUTS],
                COLUMN_BUILT, item[COLUMN_BUILT])
	    if item[COLUMN_DEFAULT] == True :#例外:當預設為真,給予勾勾圖片
		lstore.set( iter, COLUMN_DEFAULT , gtk.STOCK_APPLY)
        return lstore

    def fixed_toggled(self, cell, path, model):#判斷是否輪換
        global data, conf_file
	# 取得 toggled iter
        iter = model.get_iter((int(path),))
        fixed = model.get_value(iter, COLUMN_CHANGE)#取得真假值
        fixed = not fixed#取相反值
        #改成新值
        model.set(iter, COLUMN_CHANGE, fixed)
        inode  = model.get_string_from_iter( iter)#找出所選項目的位置
        inode = int(inode)
	en_name = data[inode][COLUMN_EN]#拉出data的英文名
	input_start = conf_file.find( '<InputMethod "%s">'%en_name)#先找出輸入法的位置
        _Circular_s = conf_file.find('Circular', input_start)
        _Circular_e = conf_file.find('\n', _Circular_s)
	
	if fixed:
	    yn_Circular = 'Yes'
	else:
	    yn_Circular = 'No'
        conf_file = conf_file[:_Circular_s] + 'Circular = ' + yn_Circular + conf_file[_Circular_e:]

    def __add_columns(self, treeview):
        model = treeview.get_model()

        # fixed toggles
        renderer = gtk.CellRendererToggle()
        renderer.connect('toggled', self.fixed_toggled, model)

        #建立5個column
	column = gtk.TreeViewColumn('輪換', renderer, active=COLUMN_CHANGE)

        # fixed 設為 50 pixels
        column.set_sizing(gtk.TREE_VIEW_COLUMN_FIXED)
        column.set_fixed_width(40)
        treeview.append_column(column)

        column = gtk.TreeViewColumn('  ', gtk.CellRendererPixbuf(),stock_id=1)
        column.set_sort_column_id(gtk.TREE_VIEW_COLUMN_FIXED)
        treeview.append_column(column)

        column = gtk.TreeViewColumn('輸入法', gtk.CellRendererText(),
                                    text=COLUMN_NAME)
        column.set_sort_column_id(COLUMN_DEFAULT)
        treeview.append_column(column)

        column = gtk.TreeViewColumn('快速鍵', gtk.CellRendererText(),
                                    text=COLUMN_SHORTCUTS)
        column.set_sort_column_id(COLUMN_NAME)
        treeview.append_column(column)

        column = gtk.TreeViewColumn('==', gtk.CellRendererText(),
                                     text=COLUMN_BUILT)
        column.set_sort_column_id(COLUMN_BUILT)
        treeview.append_column(column)


    def font_change(self,widget,fontbtn):
	#偏好字型變更函數(未完成),因get_font_name()無法傳回所需字串
	global conf_file
	new_word = fontbtn.get_font_name()
	#new_word = fontbtn.get_label()
	'''		
	font_style = fontbtn.get_value()
	font_size = fontbtn.get_action()
	font_display = fontbtn.get_activate_signal()
	print "%s,%s,%s"%(font_style , font_size, font_display)
		
	new_word = new_word.split(' ')
	new_tmp = new_word[0:-2]
	new_word=""
	for x in new_tmp:
	    new_word = new_word + x + " "
	new_word = new_word[0:-1]
	'''
	fontbtn_text = fontbtn.def_text
	conf_file[fontbtn.inode] = '%s"%s"\n'%(fontbtn_text,new_word)

    def spin_change(self,widget,spin): #變更字串
	global conf_file #廣域變數宣告,用於區域
	new_value = spin.get_value()
	new_word = '%s"%d"'%(spin.old_text, new_value )
	#合併:第一個字到新值前端+新值+新值後端至最後一字
        conf_file = conf_file[:spin.str] + new_word + conf_file[spin.end:]

    def btnchange(self,widget,ent): #變更片語值 
        new_text = ent.get_text()
	#label值,用以改變default.phr
        ent_title = ent.title
        #主程式索引所在Entry()的列數
	inode = ent.inode
        setfile = open("%s"%ent.tmp_path,'r')
        tmp_file = setfile.readlines()
        setfile.close()
        setfile = open("%s"%ent.tmp_path,'w')
        tmp_file[inode] = '%s "%s"\n'%(ent_title,new_text)
        setfile.writelines(tmp_file)
        setfile.close()

    def box_image( self, stock_id, label_text):#有圖的Button

        #建立一個box,在丟入Image 跟label 
	box1 = gtk.HBox(False, 0)
        box1.set_border_width(2)

        image = gtk.Image()
        image.set_from_stock( stock_id, 2)

        label = gtk.Label(label_text)
 
        box1.pack_start(image, 0, 0, 1)
        box1.pack_start(label, 0, 0, 1)

        image.show()
        label.show()
        return box1

    def default_input( self, btn, model, treeview):#預設輸入法
        global conf_file
	selection = treeview.get_selection()
        model, iter = selection.get_selected()

	node = 0
        for item in data:#跑總筆數
            iter1 = model.get_iter(node)#從第0個值開始
            model.set_value( iter1, COLUMN_DEFAULT , '')#全改為空值
	    node += 1
        if iter:#再將所選的,設為預設
	    model.set( iter, COLUMN_DEFAULT, gtk.STOCK_APPLY)
	#修改字串conf_file 上的預設輸入法
	inode  = model.get_string_from_iter( iter)#找出所選項目的位置
	inode = int(inode)
	en_name = data[inode][COLUMN_EN]#取出data的英文名
	def_input_s = conf_file.find('DefauleInputMethod')
	def_input_s = conf_file.find('"', def_input_s) + 1
	def_input_e = conf_file.find('"', def_input_s)
	conf_file = conf_file[:def_input_s] + en_name + conf_file[def_input_e:]
	
    def Common_set( self, Common_btn, model, treeview):#通用設定功能
        global conf_file, data
        selection = treeview.get_selection()
        model, iter = selection.get_selected()

        inode  = model.get_string_from_iter( iter)#找出所選項目的位置
        inode = int(inode)
        en_name = data[inode][COLUMN_EN]#取出data的英文名
	ch_name = data[inode][COLUMN_CH]#取出中文名
	alias_name = data[inode][COLUMN_ALIAS]#取出別名
	key = data[inode][COLUMN_KEY]#取出快捷鍵值
        dialog = gtk.Dialog("輸入法通用設定", self, 0,
                (gtk.STOCK_OK, gtk.RESPONSE_OK,
                gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL))

        hbox = gtk.HBox(False, 8)
        hbox.set_border_width(8)
        dialog.vbox.pack_start(hbox, 0, 0, 0)

        table = gtk.Table(2, 2)
        table.set_row_spacings(4)
        table.set_col_spacings(4)
        hbox.pack_start(table, 1, 1, 0)

        label = gtk.Label("輸入法：")
        #label.set_use_underline(True)
        table.attach(label, 0, 1, 0, 1)
        label = gtk.Label( ch_name)
	label.set_justify(3)
        table.attach(label, 1, 2, 0, 1)

        label = gtk.Label("別名：")
        table.attach(label, 0, 1, 1, 2)
        
	entry = gtk.Entry()
        entry.set_text(alias_name)
        table.attach(entry, 1, 2, 1, 2)
        label.set_mnemonic_widget(entry)
	
	hbox = gtk.HBox(False, 0)
	dialog.vbox.pack_start(hbox, 1, 1, 0)
	
	toggle_button = gtk.ToggleButton()
	toggle_button.connect("toggled", self.toggle_callback )	
	#hbox.pack_start(toggle_button, 1, 1, 0)
	label = gtk.Label("使用按鍵組合 Ctrl+Alt+")
	hbox.pack_start(label, True, True, 0)
	
	combox = gtk.combo_box_new_text()
	combox.append_text('請選擇0~9')
	for x in range(10):
	    combox.append_text("%s"%x)
        combox.set_active(0)
	hbox.pack_start(combox, True, True, 0)

	if key != '' :
	    key = int(key) + 1
	    combox.set_active(key)
        dialog.show_all()

        response = dialog.run()
        if response == gtk.RESPONSE_OK:
	    data[inode][COLUMN_ALIAS] = entry.get_text()#把值放入data

	    input_s = conf_file.find('<InputMethod "%s">'%en_name)
	    input_e = conf_file.find('</InputMethod>', input_s)
	#別名功能
	    if entry.get_text() == '':
		#如果原本有值,就清空
		if conf_file.find('AliasName', input_s, input_e) != -1:
		    alias_s = conf_file.find('        AliasName', input_s, input_e)  
		    alias_e = conf_file.find('\n', alias_s, input_e) +1
		    conf_file = conf_file[:alias_s] + conf_file[alias_e:]
		model.set_value( iter, COLUMN_NAME , ch_name)#更改model值為中文名
	    else:
		#如果原本無別名,就直接插入AliasName字串
		if conf_file.find('AliasName', input_s, input_e) == -1:
		    alias_s = conf_file.find('\n',input_s) +1 
		    conf_file = conf_file[:alias_s] \
			+ '        AliasName = "%s"\n'%entry.get_text() \
			+ conf_file[alias_s:]
		#如果原本有別名,就修改值
		else:
		    alias_s = conf_file.find('AliasName', input_s, input_e) 
		    alias_e = conf_file.find('\n', alias_s, input_e)
		    conf_file = conf_file[:alias_s] + 'AliasName = "%s"'%entry.get_text() + conf_file[alias_e:] 
			    
	    	model.set_value( iter, COLUMN_NAME, entry.get_text())#更改model值為別名
	#快捷鍵功能
	    node = 0
	    key_list = []
	    for item in data:
		if data[node][COLUMN_KEY] != '':
		    key_list = key_list + [data[node][COLUMN_KEY],]
		node += 1
	    key2 = combox.get_active() - 1
	    #key = str(key)#先將key轉為字串,再比對
	    if combox.get_active()  == key:
		pass
	    elif str(key2) in key_list:
		self.message_dialog()
	    elif combox.get_active() == 0:
		#如果原本有快鍵,就清空
		if conf_file.find('SetKey', input_s, input_e) != -1:
		    setkey_s = conf_file.find('        SetKey', input_s, input_e)  
		    setkey_e = conf_file.find('\n', setkey_s, input_e) +1
		    conf_file = conf_file[:setkey_s] + conf_file[setkey_e:]
		model.set_value( iter, COLUMN_SHORTCUTS, '無')#更改model值為無
		data[inode][COLUMN_KEY] = ''
	    else:
		setkey = combox.get_active() - 1
		#如果原本無快鍵,就直接插入SetKey字串
		if conf_file.find('SetKey', input_s, input_e) == -1:
		    setkey_s = conf_file.find('\n',input_s) +1 
		    conf_file = conf_file[:setkey_s] \
			+ '        SetKey = %d\n'%setkey \
			+ conf_file[setkey_s:]
		#如果原本有快建,就修改值
		else:
		    setkey_s = conf_file.find('SetKey', input_s, input_e) 
		    setkey_e = conf_file.find('\n', setkey_s, input_e)
		    conf_file = conf_file[:setkey_s] + 'SetKey = %d'%setkey + conf_file[setkey_e:] 
		data[inode][COLUMN_KEY] = str(setkey)
	    	model.set_value( iter, COLUMN_SHORTCUTS, "Ctrl+Alt+%d"%setkey)#更改model快捷鍵
        
        dialog.destroy()

    def message_dialog(self):#快速鍵重複訊息
        dialog = gtk.MessageDialog( self,
                gtk.DIALOG_MODAL | gtk.DIALOG_DESTROY_WITH_PARENT,
                gtk.MESSAGE_INFO, gtk.BUTTONS_OK,
                "您指定的快鍵，已經被其他輸入法使用了！\n \
請重新指定另一組快速鍵。")
	dialog.set_title("快速鍵重複")
        dialog.run()
        dialog.destroy()
	return 0
    def toggle_callback(self, toggle_button,  data=None):
	pass
    '''
    def changed_key(self, combox):#快速鍵功能
        model = combox.get_model()
        index = combox.get_active()
        return index
    '''
    def Property_set( self, Property_btn, model, treeview):#通用設定功能
        global conf_file, data
        selection = treeview.get_selection()
        model, iter = selection.get_selected()

        inode  = model.get_string_from_iter( iter)#找出所選項目的位置
        inode = int(inode)
        en_name = data[inode][COLUMN_EN]#取出data的英文名
	ch_name = data[inode][COLUMN_CH]#取出中文名
	alias_name = data[inode][COLUMN_ALIAS]#取出別名
	key = data[inode][COLUMN_KEY]#取出快捷鍵值
        dialog = gtk.Dialog("輸入法屬性設定", self, 0)
	dialog.set_has_separator(False)

        hbox = gtk.HBox(False, 8)
        hbox.set_border_width(8)
        dialog.vbox.pack_start(hbox, 0, 0, 0)

	vbox = gtk.VBox(False, 8)
	hbox.pack_start(vbox, 1, 0 ,0)

	label = gtk.Label("輸入法：  %s"%ch_name)
	vbox.pack_start(label, 0, 0 ,0)
	hs = gtk.HSeparator()
        vbox.pack_start(hs, 0, 0 ,0)

	ckb = gtk.CheckButton("打字時，自動顯示組字結果。")
        vbox.pack_start(ckb, 0, 0 ,0)

	ckb = gtk.CheckButton("啟用'*'、'?'萬用組字功能。")
        vbox.pack_start(ckb, 0, 0 ,0)

	ckb = gtk.CheckButton("錯誤時，按空白鍵自動清除。")
        vbox.pack_start(ckb, 0, 0 ,0)
	
	frame = gtk.Frame("自動出字模式")
        vbox.pack_start(frame, 0, 0, 10)
	shbox = gtk.HBox()
	frame.add(shbox)
	
	ckb = gtk.CheckButton("滿字根自動出字")
	shbox.pack_start(ckb, 0, 0, 0)
	ckb = gtk.CheckButton("選字鍵後移一位")
	shbox.pack_start(ckb, 0, 0, 0)

	frame = gtk.Frame("自動出字模式")
        vbox.pack_start(frame, 0, 0, 10)
	shbox = gtk.HBox()
	frame.add(shbox)
	
	ckb = gtk.CheckButton("忽略後續空白")
	shbox.pack_start(ckb, 0, 0, 0)
	ckb = gtk.CheckButton("後續空白視為有效")
	shbox.pack_start(ckb, 0, 0, 0)
	
	ckb = gtk.CheckButton("按下結束鍵出字")
        vbox.pack_start(ckb, 0, 0 ,0)
	
	'''
	自動出字模式 滿字根自動出字 選字鍵後移一位
	忽略後續空白 後續空白視為有效
	按下結束鍵出字。 特殊字根設定：
	'''
	vbox = gtk.VBox(False, 8)
	hbox.pack_start(vbox, 1, 0 ,0)

	ok_btn = gtk.Button(stock='gtk-ok')
	ok_btn.connect("clicked", self.dialog_quit, dialog)
	vbox.pack_start(ok_btn, 1, 0 ,0)
	quit_btn = gtk.Button(stock='gtk-cancel')
	quit_btn.connect("clicked", self.dialog_quit, dialog)
	vbox.pack_start(quit_btn, 1, 0 ,0)
	def_btn = gtk.Button('預設值')
	def_btn.connect("clicked", self.dialog_quit, dialog)
	vbox.pack_start(def_btn, 1, 0 ,0)
		
        dialog.show_all()
        response = dialog.run()
	#if response == -1:
	#    print 'ture'
	    #dialog.destroy()
	dialog.destroy() 

    def dialog_quit(self, quit_btn, dialog):
	dialog.destroy()

    def selfile(slef, wiget, selentry):
	dialog = gtk.FileChooserDialog("Open..",
				       None,
				       gtk.FILE_CHOOSER_ACTION_OPEN,
				       (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,
					gtk.STOCK_OPEN, gtk.RESPONSE_OK))
	dialog.set_default_response(gtk.RESPONSE_OK)

	filter = gtk.FileFilter()
	filter.set_name("All files")
	filter.add_pattern("*")
	dialog.add_filter(filter)

	filter = gtk.FileFilter()
	filter.set_name("cin")
	filter.add_mime_type("cin")
	filter.add_mime_type("cin/gz")
	filter.add_mime_type("tab")
	filter.add_pattern("*.cin")
	filter.add_pattern("*.cin.gz")
	filter.add_pattern("*.tab")
	dialog.add_filter(filter)

	response = dialog.run()
	if response == gtk.RESPONSE_OK:
	    selentry.set_text(dialog.get_filename())
	    print dialog.get_filename()
	elif response == gtk.RESPONSE_CANCEL:
	    pass 
	dialog.destroy()
	
    def install_cin(self, wiget):
	#insdialog = gtk.Dialog("安裝輸入法", self, 0,
        #        (gtk.STOCK_OK, gtk.RESPONSE_OK,
        #        gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL))
        insdialog = gtk.Dialog("安裝輸入法", self, 0)
	insdialog.set_has_separator(False)

        hbox = gtk.HBox(False, 8)
        hbox.set_border_width(8)
        insdialog.vbox.pack_start(hbox, 0, 0, 0)

	#左部
	vbox = gtk.VBox(False, 8)

	notebook = gtk.Notebook()
        notebook.set_tab_pos(gtk.POS_TOP)
	#table = gtk.Table(10, 10, 1)
	table = gtk.Table(10, 10, False)
	label = gtk.Label("請輸入檔案完整路徑名稱，或按一下「瀏覽」\n \
按鈕選擇；如果是*.cin檔案的話，請確定該檔\n \
是UTF-8編碼。")
	table.attach(label, 0, 10, 0, 3)
	selentry = gtk.Entry()
	table.attach(selentry, 0, 10, 3, 4)
	btn = gtk.Button("瀏覽")
	btn.connect("clicked", self.selfile, selentry)
	table.attach(btn, 8, 10, 4, 5)
	label = gtk.Label('%s'%('\n'*10))
	table.attach(label, 0, 10, 5, 10)
	label = gtk.Label("從本機安裝")
        notebook.append_page(table, label)

	table = gtk.Table(10, 10, 1)
	label = gtk.Label("從網路安裝")
	#tview = gtk.TreeView(
        #self.liststore = gtk.ListStore(str, 'gboolean')
        #self.treeview = gtk.TreeView(self.liststore)
        #self.tvcolumn = gtk.TreeViewColumn('請選擇下載站台')
	#叫出設定檔並存成串列
	home_path = os.environ['HOME']
	#判斷家目錄.oxim/下oxim.conf是否存在
	mirrors_site = open('%s/.oxim/mirrors.site'%home_path, 'r')
	input = open('%s/.oxim/mirrors.site'%home_path ,'r')
	mirrors_list = input.read()
	input.close()

	print mirrors_list
	print '========='
	
	#mirrors_list.split('=')
	n = 0
	#for x in mirrors_list.split(' = '):
	    #n += 1
	    #if n%2 == 1 :
	   
	    #print x[0]
	for x in mirrors_list.lstrip(''):
	    print x 
        self.treestore = gtk.ListStore(str)
        #chb = gtk.CheckButton()
        self.treestore.append(['宜蘭梗枋國小'])
        self.treestore.append(['宜蘭縣網中心'])
        self.treestore.append(['新竹縣網'])
        self.treestore.append(['宜蘭頭城國小'])
        self.treestore.append(['臺北縣大豐國小'])
        self.treestore.append(['國家高速網路與計算中心'])
        self.treestore.append(['元智大學資訊工程系'])
        #ter = self.treestore.append(['4'])
        #ter1 = self.treestore.insert_before(ter,['4line'])
        #self.treestore.swap(ter,ter1)
        # we'll add some data now - 4 rows with 3 child rows each
        #print self.treestore[0]
        #for parent in range(4):
        #    self.treestore.append(  ,['parent %i' % parent])
        '''
            for child in range(3):
                self.treestore.append(piter, ['child %i of parent %i' %
                                              (child, parent)])
        '''
        # create the TreeView using treestore
        self.treeview = gtk.TreeView(self.treestore)

        # create the TreeViewColumn to display the data
        self.tvcolumn = gtk.TreeViewColumn('請選擇下載站台')

        # add tvcolumn to treeview
        self.treeview.append_column(self.tvcolumn)

        # create a CellRendererText to render the data
        self.cell = gtk.CellRendererText()

        # add the cell to the tvcolumn and allow it to expand
        self.tvcolumn.pack_start(self.cell, True)

        # set the cell "text" attribute to column 0 - retrieve text
        # from that column in treestore
        self.tvcolumn.add_attribute(self.cell, 'text', 0)

        # make it searchable
        self.treeview.set_search_column(0)

        # Allow sorting on the column
        self.tvcolumn.set_sort_column_id(1)

        # Allow drag and drop reordering of rows
        self.treeview.set_reorderable(1)

	table.attach(self.treeview, 0, 10, 0, 9)
        notebook.append_page(table, label)

	cbtn = gtk.Button('連線')
	table.attach(cbtn, 8, 10, 9, 10)
	
	#table = gtk.Table(10, 10, 1)
        vbox.pack_start(notebook, 1, 0 ,0)
	#table.attach(notebook, 0, 10, 0, 9)
	hbox.pack_start(vbox, 1, 0 ,0)



	#右部
	vbox = gtk.VBox(False, 1)
	hbox.pack_start(vbox, 1, 0 ,0)
	ok_btn = gtk.Button(stock='gtk-ok')
	ok_btn.connect("clicked", self.dialog_quit, insdialog)
	vbox.pack_start(ok_btn, 0, 0 ,10)
	quit_btn = gtk.Button(stock='gtk-cancel')
	quit_btn.connect("clicked", self.dialog_quit, insdialog)
	vbox.pack_start(quit_btn, 0, 0 ,0)
	hbox.pack_start(vbox, 0, 0, 0)

	insdialog.show_all()

	
    def __init__(self):
	window = gtk.Window()
	#window = gobject.new(gtk.Window, resizable=FALSE)
	window.set_default_size(450,300)
	window.connect('destroy', gtk.main_quit)
	#window.set_allow_grow(0)
	window.set_resizable(1)
	window.set_position(gtk.WIN_POS_CENTER)
	window.set_border_width(8)	
	window.set_title("Open X Input Method 輸入法設定")	

        global conf_file, data
	notebook = gtk.Notebook()
        notebook.set_tab_pos(gtk.POS_TOP)
	table = gtk.Table(10, 10, 1)
        window.add(table)
	table.attach(notebook, 0, 10, 0, 9)

        #輸入法頁
	table2 = gtk.Table(20, 20, 0)
        
        sw = gtk.ScrolledWindow()
        sw.set_shadow_type(gtk.SHADOW_ETCHED_IN)
        sw.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
	
	#conf_list = conf_file.split('\n')#將str 轉成list
	################## 開始掃conf 的資料到data 裡 ######################################
	data = [] #data 先清空
	#找出預設的輸入法
	def_input_s = conf_file.find('DefauleInputMethod')
	def_input_s = conf_file.find('"', def_input_s) + 1
	def_input_e = conf_file.find('"', def_input_s)
	def_input = conf_file[def_input_s:def_input_e]

	input_start = conf_file.find('</SystemSetting>')
	while input_start != -1:
	    input_end = conf_file.find('</InputMethod>',input_start)
	    #先取出四個tree 的必要資料
	    ch_name_s = conf_file.find('#', input_start)+1
	    ch_name_s = conf_file.find('#', ch_name_s)+1
	    ch_name_e = conf_file.find('\n', ch_name_s)
	    ch_name = conf_file[ch_name_s:ch_name_e]
	    ch_name = ch_name.replace(' ', '')
	    use_name = ch_name  

	    en_name_s = conf_file.find('InputMethod', input_start)
	    en_name_s = conf_file.find('"', en_name_s)+1
	    en_name_e = conf_file.find('"', en_name_s)
	    en_name = conf_file[en_name_s:en_name_e]

	    _Circular_s = conf_file.find('Circular', input_start) 
	    _Circular_e = conf_file.find('\n', _Circular_s)
	    _Circular = conf_file[_Circular_s:_Circular_e]
	    _Circular = _Circular.replace('"', '')

	    def_method = ''
	    if ch_name in ['中標注音','中標倉頡','新酷音','萬國碼']:
		def_method = '<內建>'

	    yn_Circular = False
	    if _Circular == 'Circular = Yes':
		yn_Circular = True
	    
	    key_list = ''
	    _SetKey = '無'
	    yn = conf_file.find('SetKey', input_start, input_end)
	    if yn != -1:
		_SetKey_s = conf_file.find('SetKey', input_start)
		_SetKey_s = conf_file.find('=', _SetKey_s)+1
		_SetKey_e = conf_file.find('\n', _SetKey_s)
		_SetKey = conf_file[_SetKey_s:_SetKey_e]
		_SetKey = _SetKey.replace('"','')
		_SetKey = _SetKey.replace(' ','')
	        key_list = _SetKey
		_SetKey = "Ctrl+Alt+%s"%_SetKey

	    yn = conf_file.find('AliasName', input_start, input_end)
	    _AliasName = ''
	    if yn != -1:
		_AliasName_s = conf_file.find('AliasName', input_start)
		_AliasName_s = conf_file.find('"', _AliasName_s)+1
		_AliasName_e = conf_file.find('"', _AliasName_s)
		_AliasName = conf_file[_AliasName_s:_AliasName_e]
		use_name = _AliasName
	    alias_name = _AliasName
	    yn_def = False
	    if en_name == def_input:
		yn_def = True

	    data = data + [[yn_Circular, yn_def, use_name, _SetKey, def_method,
				 en_name, ch_name, alias_name, key_list],]
	    input_start = conf_file.find('#', input_end)

	################################# 結東掃conf #######################################
        # 建立tree model
        model = self.__create_model()
        # 建立 tree view
        treeview = gtk.TreeView(model)
        treeview.set_rules_hint(True)
        treeview.set_search_column(COLUMN_BUILT)

        sw.add(treeview)

        # 加入 columns 
        self.__add_columns(treeview)
        
	#vbox = gtk.VBox()
	#vobx.pack_start( sw, 0, 1, 1)
        vbox = gtk.VBox()
        vbox.pack_start( sw, 1, 1, 1)
	table2.attach( vbox, 0, 17, 0, 17)


	#空白格
	hbox = gtk.HBox()
	table2.attach(hbox, 17, 20, 0, 13)
	
	insbtn = gtk.Button()
	box1 = self.box_image( "gtk-add", "安裝輸入法")
	insbtn.connect("clicked", self.install_cin)
	insbtn .add(box1)#將有圖的box 裝入Button
	table2.attach(insbtn, 0, 7, 18, 19)

	movbtn = gtk.Button()
	box1 = self.box_image( "gtk-delete", "移除輸入法")
	movbtn .add(box1)
	table2.attach(movbtn, 10, 17, 18, 19)
	
	vbox = gtk.VBox()

	def_btn = gtk.Button()
	#tbtn1.set_relief(gtk.RELIEF_HALF)
	box1 = self.box_image( "gtk-apply", "預設")
	def_btn = gtk.Button()
	def_btn.add(box1)
	def_btn.connect("clicked", self.default_input, model, treeview)
	vbox.pack_start( def_btn, 1, 1, 0)
	
	Common_btn = gtk.Button("通用設定")
	Common_btn.connect("clicked", self.Common_set, model, treeview)
	vbox.pack_start( Common_btn, 1, 1, 0)
	
	Property_btn = gtk.Button("屬性")
	Property_btn.connect("clicked", self.Property_set, model, treeview)
	vbox.pack_start( Property_btn, 1, 1, 0)

	table2.attach( vbox, 17, 20, 13, 16)
	
	label = gtk.Label("輸入法")
	notebook.append_page(table2, label)

	#字型頁
	table2 = gtk.Table(20, 20, 0)
        label = gtk.Label("偏好字型：")
	#偏好字型功能(未完成)
	table2.attach(label, 0, 5, 2, 3)
	fontbtn = gtk.FontButton()
        '''
	old_text = "%s"%conf_file[1]
	tmp_text = old_text.split('"')
	old_word = tmp_text[1]
	fontbtn.set_use_font(True)
	fontbtn.set_show_style(False)
	fontbtn.set_show_size(False)
	fontbtn.set_use_size(False)
	#fontbtn.set_use_style(False)
	fontbtn.set_font_name(old_word)
	fontbtn.def_text = tmp_text[0]
	fontbtn.inode = 1 
	'''
	fontbtn.connect("font-set",self.font_change,fontbtn)
	#opt = gtk.OptionMenu()
	table2.attach(fontbtn, 5, 19, 2, 3)
	
	frame = gtk.Frame("字型大小(Pixels)")
	table2.attach(frame, 0, 20, 4, 20)
	
	vbox = gtk.VBox()
	label = gtk.Label("組字區：")
        vbox.pack_start(label, 1, 0, 0)
        label = gtk.Label("選字區：")
        vbox.pack_start(label, 1, 0, 0)
        label = gtk.Label("狀態區：")
        vbox.pack_start(label, 1, 0, 0)
        label = gtk.Label("快速選單：")
        vbox.pack_start(label, 1, 0, 0)
        label = gtk.Label("符號表：")
        vbox.pack_start(label, 1, 0, 0)
        label = gtk.Label("XCIN風格：")
        vbox.pack_start(label, 1, 0, 0)
	table2.attach(vbox, 0, 4, 5, 20)
	
	vbox = gtk.VBox()
	#組字區
	spin = gtk.SpinButton( None, 1, 0)
	#找出設定文字,在字串的開始和結束位置,及設定數值的結束位置
	find_start = conf_file.find('PreeditFontSize = ')
	find_end = conf_file.find('"',find_start, )
	find_value = conf_file.find('\n',find_end, )

	spin.old_text = conf_file[find_start:find_end] #找出字串
        spin.old_value = conf_file[find_end:find_value] #找出數值,含""
	old_value = spin.old_value.replace('"','') #去除""
	old_value = int(old_value) #轉為spinbutton能用的數值
	
	spin.str = find_start #記錄整字串起值終值,為函式變更字串用
	spin.end = find_value

	spin.set_increments( 1, 1)
	spin.set_range(12,48)
	spin.set_value(old_value)
	spin.connect("changed",self.spin_change,spin)
	vbox.pack_start(spin, 1, 0, 0)
	
	#選字區
        spin = gtk.SpinButton( None, 1, 0)

        find_start = conf_file.find('SelectFontSize = ')
        find_end = conf_file.find('"',find_start, )
        find_value = conf_file.find('\n',find_end, )

        spin.old_text = conf_file[find_start:find_end]
        spin.old_value = conf_file[find_end:find_value]
        old_value = spin.old_value.replace('"','')
        old_value = int(old_value)

        spin.str = find_start
        spin.end = find_value

        spin.set_increments( 1, 1)
        spin.set_range(12,48)
        spin.set_value(old_value)
        spin.connect("changed",self.spin_change,spin)
        vbox.pack_start(spin, 1, 0, 0)
	#狀態區
        spin = gtk.SpinButton( None, 1, 0)

        find_start = conf_file.find('StatusFontSize = ')
        find_end = conf_file.find('"',find_start, )
        find_value = conf_file.find('\n',find_end, )

        spin.old_text = conf_file[find_start:find_end]
        spin.old_value = conf_file[find_end:find_value]
        old_value = spin.old_value.replace('"','')
        old_value = int(old_value)

        spin.str = find_start
        spin.end = find_value

        spin.set_increments( 1, 1)
        spin.set_range(12,18)
        spin.set_value(old_value)
        spin.connect("changed",self.spin_change,spin)
        vbox.pack_start(spin, 1, 0, 0)
	#快速選單
        spin = gtk.SpinButton( None, 1, 0)

        find_start = conf_file.find('MenuFontSize = ')
        find_end = conf_file.find('"',find_start, )
        find_value = conf_file.find('\n',find_end, )

        spin.old_text = conf_file[find_start:find_end]
        spin.old_value = conf_file[find_end:find_value]
        old_value = spin.old_value.replace('"','')
        old_value = int(old_value)

        spin.str = find_start
        spin.end = find_value

        spin.set_increments( 1, 1)
        spin.set_range(12,20)
        spin.set_value(old_value)
        spin.connect("changed",self.spin_change,spin)
        vbox.pack_start(spin, 1, 0, 0)
	#符號表
        spin = gtk.SpinButton( None, 1, 0)

        find_start = conf_file.find('SymbolFontSize = ')
        find_end = conf_file.find('"',find_start, )
        find_value = conf_file.find('\n',find_end, )

        spin.old_text = conf_file[find_start:find_end]
        spin.old_value = conf_file[find_end:find_value]
        old_value = spin.old_value.replace('"','')
        old_value = int(old_value)

        spin.str = find_start
        spin.end = find_value

        spin.set_increments( 1, 1)
        spin.set_range(12,24)
        spin.set_value(old_value)
        spin.connect("changed",self.spin_change,spin)
        vbox.pack_start(spin, 1, 0, 0)
	#XCIN風格
        spin = gtk.SpinButton( None, 1, 0)

        find_start = conf_file.find('XcinFontSize = ')
        find_end = conf_file.find('"',find_start, )
        find_value = conf_file.find('\n',find_end, )

        spin.old_text = conf_file[find_start:find_end]
        spin.old_value = conf_file[find_end:find_value]
        old_value = spin.old_value.replace('"','')
        old_value = int(old_value)

        spin.str = find_start
        spin.end = find_value

        spin.set_increments( 1, 1)
        spin.set_range(12,48) 
        spin.set_value(old_value)
        spin.connect("changed",self.spin_change,spin)
	vbox.pack_start(spin, 1, 0, 0)
	
	table2.attach(vbox, 4, 7, 5, 20)
	#字型功能結束
	vbox = gtk.VBox()
	pixbufanim = gtk.gdk.PixbufAnimation("images/sample.bmp")
	image = gtk.Image()
	image.set_from_animation(pixbufanim)
	table2.attach(image, 7, 12, 5, 20)
	#table2.attach(label, 0, 5, 2, 3)
	
	label = gtk.Label("字型")
        notebook.append_page(table2, label)

	#片語頁
        table2 = gtk.Table(20, 20, 0)
	scrolled_window = gtk.ScrolledWindow()
	scrolled_window.set_border_width(10)
	scrolled_window.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_ALWAYS)
	table2.attach(scrolled_window, 0, 16, 1, 19)
        #判斷家目錄下default.phr是否存在,不存在則複製一個(shell script)寫法
        #os.system('test -e ~/.oxim/tables/default.phr || cp /usr/lib/oxim/tables/default.phr ~/.oxim/tables/')
        #拉出家目錄的位置
	tmp_path = os.environ['HOME']
	#判斷家目錄下default.phr是否存在
	if not os.path.exists("%s/.oxim/tables/default.phr"%tmp_path):
	    #不存在則複製一個
	    shutil.copyfile('/usr/lib/oxim/tables/default.phr','%s/.oxim/tables/default.phr'%tmp_path)
	defile = open("%s/.oxim/tables/default.phr"%tmp_path)
        inode = 0
        vbox = gtk.VBox()
        while 1:
            tmp_word = defile.readline()
	    if not tmp_word:break #如果傳入值為空,即跳出
	    #tmp_title=label的值,tmp_text=enty的值
	    tmp_word = tmp_word.rstrip()
            tmp_title = tmp_word[0:1]
            tmp_text = tmp_word[2:]
            tmp_text = tmp_text.replace('"','')
            ent = gtk.Entry(0)
            elabel = gtk.Label()
            elabel.set_text("%s"%(tmp_title))
            ent.set_text("%s"%(tmp_text))
            ent.inode = inode
            ent.title = tmp_title
            ent.tmp_path = "%s/.oxim/tables/default.phr"%(tmp_path)
            ent.connect("changed",self.btnchange,ent)
            hbox = gtk.HBox(0,0)
            hbox.pack_end(ent, 0, 0, 0)
            hbox.pack_end(elabel, 0, 0, 0)
            vbox.pack_start(hbox, 0, 0, 0)
            inode = inode + 1
            #if not tmp_word:break
        defile.close()

	#vbox.pack_start(label, 1, 0, 0)
	scrolled_window.add_with_viewport(vbox)
	label = gtk.Label()
	label.set_markup("<span foreground='#000080'>\n您可以在左方的表格內，建立您經常\
使用的片語、詞句或是符號，往後在輸入的時候，就可以搭配 Alt+Shift 按鍵，達到快速輸入的目的。</span>")
	label.set_line_wrap(1)
	label.set_width_chars(20)
	vbox = gtk.VBox( 0, 0)
	vbox.pack_start(label, 0, 0, 0)
	table2.attach(vbox, 16, 20, 1, 19)
	label = gtk.Label("片語")
        notebook.append_page(table2, label)

        #關於頁
	table2 = gtk.Table( 10, 10, 0)
	vbox = gtk.VBox()
	label = gtk.Label()
	label.set_markup("<span foreground='blue' size='x-large'>Open X Input Method Setup 1.5.5</span>")
	#label.set_justify(gtk.JUSTIFY_LEFT)
	vbox.pack_start(label, 1, 0, 0)
	label = gtk.Label("作者：Firefly<firefly@opendesktop.org.tw>")
	vbox.pack_start(label, 1, 0, 0)
        label = gtk.Label("      Gene(PyGTK)<gene@server1.ossii.com.tw>")
        vbox.pack_start(label, 1, 0, 0)
	label = gtk.Label("網址：http://opendesktop.org.tw")
	vbox.pack_start(label, 1, 0, 0)
	label = gtk.Label("授權宣告：")
	vbox.pack_start(label, 1, 0, 0)
	table2.attach(vbox, 0, 10, 0, 4)

	#vbox = gtk.VBox()
	textview = gtk.TextView()
	scrolled_window = gtk.ScrolledWindow()
	scrolled_window.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
	textbuffer = textview.get_buffer()
	infile = open("Copyright", "r")
	if infile:
	    string = infile.read()
	    infile.close()
	    textbuffer.set_text(string)

	scrolled_window.add(textview)
	table2.attach(scrolled_window, 0, 10, 4, 10)
	label = gtk.Label("關於")
        notebook.append_page(table2, label)
	
	hbox = gtk.HBox()
        btn1 = gtk.Button(stock='gtk-ok')
        btn1.connect("clicked",self.setconf )
	hbox.pack_start(btn1, 1, 1, 10)
	btn2 = gtk.Button(stock='gtk-cancel')
        btn2.connect("clicked", gtk.main_quit, None)
	hbox.pack_start(btn2, 1, 1, 10)
        table.attach(hbox, 0, 10, 9, 10)

	window.show_all()
def main():
    gtk.main()
if __name__ == "__main__":
    oximsetup()
    main()
#顯示行號 (nu)、展開跳格鍵 (et)，指定跳格字元為 4 (ts=4)、偏移字元寬為 4 (sw=4)、C 式縮排為 >4 (cino=>4)
