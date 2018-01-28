import os, re, shutil
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import askdirectory
from tkinter.ttk import Progressbar, Notebook

window = Tk()
win_width = 380
win_height = 340
half_width = win_width/2
half_height = win_height/2

window.geometry(str(win_width) + 'x' + str(win_height))
window.resizable(False, False)
window.title("File Organizer")

directory_name = Entry(window, width=59)
directory_name.grid(column=0, row=1, sticky=W, padx=10, pady=10)

file_type_notebook = Notebook(window)
file_type_notebook.grid(column=0, row=3, sticky=N+W, padx=10, pady=10)

bar = Progressbar(window, length=360)

tab_img = Listbox(file_type_notebook)
tab_vid = Listbox(file_type_notebook)
tab_zip = Listbox(file_type_notebook)
tab_doc = Listbox(file_type_notebook)
tab_exe = Listbox(file_type_notebook)
tab_aud = Listbox(file_type_notebook)

tabs = [tab_img, tab_zip, tab_doc, tab_exe, tab_vid, tab_aud]

file_type_notebook.add(tab_img, text="Images")
file_type_notebook.add(tab_zip, text="Compressed")
file_type_notebook.add(tab_doc, text="Documents")
file_type_notebook.add(tab_exe, text="Programs")
file_type_notebook.add(tab_vid, text="Videos")
file_type_notebook.add(tab_aud, text="Audio")

type_file_zip = ('zip','rar','7z','cab')
type_file_img = ('png','jpg','jpeg','gif','ico','bmp','cpt','psd','psp','xcf','ppm','pgm','pbm','pnm')
type_file_vid = ('webm','mkv','flv','vob','drc','gifv','mng','avi','mov','qt','wmv','yuv','rm',
                 'rmvb','asf','mp4','m4p','m4v','mpg','mp2','mpeg','mpe','mpv','3gp','3g2','flv','f4v','f4p')
type_file_aud = ('aa','aac','aax','act','aiff','amr','ape','au','dvf','flac','m4a','m4b','mp3','mp3','mogg',
                 'ra','rm','vox','wav','tta','wma','wv')
type_file_doc = ('doc','docx','ppt','pptx','xls','xlsx','pdf','txt','xml','html','css','js','php')
type_file_exe = ('bat','exe','msi','apk','cmd','bin','lnk')
    
def get_directory():
    for tab in tabs:
        tab.delete(0, 'end')
    dir_name = askdirectory()
    if not dir_name == '':                 #clear entry if cancel button is pressed on askdirectory dialog
        directory_name.delete(0, 'end')
    directory_name.insert(0, dir_name)
    files = get_files()
    for file in files:
        if str(file).lower().endswith(type_file_zip):
            tab_zip.insert(0, file)
        if str(file).lower().endswith(type_file_img):
            tab_img.insert(0, file)
        if str(file).lower().endswith(type_file_doc):
            tab_doc.insert(0, file)
        if str(file).lower().endswith(type_file_exe):
            tab_exe.insert(0, file)
        if str(file).lower().endswith(type_file_vid):
            tab_vid.insert(0, file)
        if str(file).lower().endswith(type_file_aud):
            tab_aud.insert(0, file) 
        
btn_get_directory = Button(window, text="Choose Directory", command=get_directory)
btn_get_directory.grid(column=0, row=2, sticky=N+W, padx=10)

def create_organize_button():
    btn_get_file = Button(window, text="Organize", command=organize_files)
    btn_get_file.grid(column=0, row=2, sticky=N+W, padx=120)
    return btn_get_file
    
def move_files(file, type_dir_name):
    if not os.path.isdir(type_dir_name):
        os.makedirs(type_dir_name)
    shutil.move(os.path.abspath(file), os.path.join(os.getcwd(), type_dir_name, file))
    
def check_path():
    return os.path.exists(directory_name.get())
    
def path_does_not_exist():
    messagebox.showerror('Incorrect Path', 'Path does not exist\nPlease choose a correct path')
        
def get_files():
    os.chdir(directory_name.get())
    files = os.listdir(directory_name.get())
    return files
    
def organize_files():
    if check_path():
        files = get_files()
        bar.grid(column=0, row=4, sticky=S+W, padx=10, pady=10)
    
        for file in files:
            if str(file).lower().endswith(type_file_zip):
                type_dir_name = 'Compressed'
                move_files(file, type_dir_name)
            if str(file).lower().endswith(type_file_img):
                type_dir_name = 'Images'
                move_files(file, type_dir_name)
            if str(file).lower().endswith(type_file_doc):
                type_dir_name = 'Documents'
                move_files(file, type_dir_name)
            if str(file).lower().endswith(type_file_exe):
                type_dir_name = 'Programs'
                move_files(file, type_dir_name)
            if str(file).lower().endswith(type_file_vid):
                type_dir_name = 'Videos'
                move_files(file, type_dir_name)
            if str(file).lower().endswith(type_file_aud):
                type_dir_name = 'Audio'
                move_files(file, type_dir_name)
            bar['value'] += (100/len(files))
    else:
        path_does_not_exist()
        
create_organize_button()
    
window.mainloop()
