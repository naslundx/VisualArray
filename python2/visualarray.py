# VisualArray for Python, version 0.1

import Tkinter
from time import sleep
from random import randint

class VisualArray:
	def __init__(self, value, defaultnocolor="white", defaultcolor="green", defaultseparatorcolor="red", autostart=False, animationspeed=100, width=200, height=200):
		# Copy array
		if isinstance(value,list):
			self.data = list(value)
		else:
			self.data = []

		# Action queue
		self.original = list(self.data)
		self.action_queue = []
		self.action_queue_played = []

		# Graphics settings
		self.gfx_defaultcolor = defaultcolor
		self.gfx_defaultseparatorcolor = defaultseparatorcolor
		self.gfx_defaultnocolor = defaultnocolor
		self.gfx_initwait = 500
		self.gfx_autostart = autostart
		self.gfx_playing = autostart
		self.gfx_speed = animationspeed
		self.gfx_bottom = height
		self.gfx_right = width
		self.gfx_latest = []


	def __getitem__(self, key):
		if isinstance(key, slice):
			return VisualArray(self.data[key])
		else:
			return self.data[key]


	def __setitem__(self, key, value):
		self.data[key] = value
		self.action_queue.append([key,value])


	def __str__(self):
		return str(self.data)


	def __iter__(self):
		for x in self.data:
			yield x


	def __len__(self):
		return len(self.data)


	def __eq__(self, other):
		if isinstance(other, list):
			return self.data == other
		elif isinstance(other, VisualArray):
			return self.data == other.data


	def __ne__(self, other):
		return not self.__eq__(other)


	def hide_latest_operation(self):
		if len(self.action_queue)>0:
			self.action_queue.pop()


	def append(self, value):
		self.data.append(value)
		self.original.append(value)
		self.clear_history()


	def clear_history(self):
		self.original = list(self.data)
		self.action_queue = []
		self.action_queue_played = []


	def next_operation(self):
		if self.action_queue:
			top = self.action_queue.pop(0)

			if isinstance(top[0], int):
				if self.action_queue != []:
					nelem = self.action_queue[0]
					if isinstance(nelem[0], int):
						if top[1] == self.original[nelem[0]] and nelem[1] == self.original[top[0]]:
							self.action_queue.pop(0)
							return ['swap', top[0], nelem[0]]

			return top
		else:
			return None


	def prev_operation(self):
		if self.action_queue_played:
			top = self.action_queue_played.pop()
			return top

		else:
			return None


	def gfx_color(self, index, color=None):
		if index >= 0 and index < len(self.data):
			if not color:
				color = self.gfx_defaultcolor

			self.action_queue.append(["color", index, color])


	def gfx_decolor(self, index):
		if index >= 0 and index < len(self.data):
			self.action_queue.append(["decolor", index])


	def gfx_separate(self, left_index, color=None, width=3.0):
		if left_index >= -1 and left_index <= len(self.data):
			if not color:
				color = self.gfx_defaultseparatorcolor
			self.action_queue.append(["separate", left_index, color, width])


	def gfx_deseparate(self, left_index):
		if left_index >= -1 and left_index <= len(self.data):
			self.action_queue.append(["deseparate", left_index])


	def gui_play(self):
		if self.gfx_playing:
			self.gui_play['text'] = 'Play'
			self.gfx_playing = False
		else:
			self.gui_play['text'] = 'Pause'
			self.canvas.after(100, self.render_next)
			self.gfx_playing = True


	def gui_restart(self):
		while self.action_queue_played:
			self.gui_stepprev()


	def gui_stepnext(self):
		self.render_next(repeat=False)


	def gui_stepprev(self):
		self.render_prev()


	# A subclass of Canvas for dealing with resizing of windows
	class ResizingCanvas(Tkinter.Canvas):
		def __init__(self, parent, **kwargs):
			Tkinter.Canvas.__init__(self, parent, **kwargs)
			self.height = self.winfo_reqheight()
			self.width = self.winfo_reqwidth()
			self.bind("<Configure>", self.on_resize)

		def on_resize(self, event):
			# determine the ratio of old width/height to new width/height
			wscale = float(event.width) / self.width
			hscale = float(event.height) / self.height
			self.width = event.width
			self.height = event.height
			#resize the canvas
			self.config(width = self.width, height = self.height)
			# rescale all the objects tagged with the "all" tag
			self.scale("all", 0, 0, wscale, hscale)


	def render(self):
		# Set gfx constants
		self.gfx_top = 0
		self.gfx_left = 0	
		self.gfx_windowmargin = 10 
		self.gui_space = 30 
		self.gfx_scale = (self.gfx_bottom - self.gfx_top - self.gfx_windowmargin) / max(self.data)
		self.gfx_rectwidth = (self.gfx_right - self.gfx_left - self.gfx_windowmargin) / len(self.data)		

		# Init graphics window
		self.root = Tkinter.Tk()
		self.root.title("VisualArray")
		self.root.geometry(str(self.gfx_bottom+self.gfx_windowmargin)+"x"+str(self.gfx_right+self.gfx_windowmargin+self.gui_space))
		#self.frame = Tkinter.Frame(self.root) # DK
		#self.frame.pack(fill = Tkinter.BOTH) # DK
		#self.frame.pack(fill = Tkinter.BOTH, expand = Tkinter.YES) # DK
		#self.canvas = Tkinter.Canvas(self.root) # DK
		self.canvas = self.ResizingCanvas(self.root) # DK
		#self.canvas = self.ResizingCanvas(self.frame) # DK
		#self.canvas.pack(fill = Tkinter.BOTH) # DK
		#self.canvas.pack(fill = Tkinter.BOTH, expand = Tkinter.YES) # DK
		
		# Create rectangles
		self.gfx_rectangles = []
		self.gfx_separators = []
		for i in range(len(self.original)):
			rect = self.canvas.create_rectangle(self.gfx_windowmargin + self.gfx_left + i*self.gfx_rectwidth, 
												self.gfx_windowmargin + self.gfx_top, 
												self.gfx_windowmargin + self.gfx_left + (i+1)*self.gfx_rectwidth, 
												self.gfx_windowmargin + self.gfx_top + self.original[i]*self.gfx_scale)
			self.canvas.itemconfig(rect, fill=self.gfx_defaultnocolor)
			self.gfx_rectangles.append(rect)

		self.gui_play = Tkinter.Button(self.canvas,text='Play', command=self.gui_play)
		self.gui_restart = Tkinter.Button(self.canvas,text='Restart', command=self.gui_restart)
		self.gui_prev = Tkinter.Button(self.canvas,text='<', command=self.gui_stepprev)
		self.gui_next = Tkinter.Button(self.canvas,text='>', command=self.gui_stepnext)
		#self.canvas.create_window(30, self.gfx_bottom+20, window=self.gui_play)
		self.canvas.create_window(30, self.gfx_bottom+20, window=self.gui_play, tags = "all")
		#self.canvas.create_window(90, self.gfx_bottom+20, window=self.gui_restart)
		self.canvas.create_window(90, self.gfx_bottom+20, window=self.gui_restart, tags = "all")
		#self.canvas.create_window(145, self.gfx_bottom+20, window=self.gui_prev)
		self.canvas.create_window(145, self.gfx_bottom+20, window=self.gui_prev, tags = "all")
		#self.canvas.create_window(183, self.gfx_bottom+20, window=self.gui_next)
		self.canvas.create_window(183, self.gfx_bottom+20, window=self.gui_next, tags = "all")

		#self.canvas.pack(fill=Tkinter.BOTH) # DK
		self.canvas.pack(fill = Tkinter.BOTH, expand = Tkinter.YES) # DK

		# Start playback
		if self.gfx_autostart:
			self.canvas.after(self.gfx_initwait, self.render_next)
			self.canvas.itemconfig(self.gui_play, text='Pause')

		self.canvas.addtag_all("all") # DK
		self.root.mainloop()  


	def render_next(self, repeat=True):
		op = self.next_operation()
		flip = self.flipped_operation(op)	

		for item in self.gfx_latest:
			self.canvas.itemconfig(item, fill=self.gfx_defaultnocolor)
		self.gfx_latest = []
		
		if op:					
			self.execute_operation(op)
			self.action_queue_played.append(flip)

			if repeat and self.gfx_playing:
				self.canvas.after(self.gfx_speed, self.render_next)

		else:
			self.gui_play['text']='Play'
			self.gfx_playing = False
		

	def render_prev(self):
		if self.gfx_playing:
			self.gfx_playing = False
			self.gui_play['text']='Play'

		for item in self.gfx_latest:
			self.canvas.itemconfig(item, fill=self.gfx_defaultnocolor)
		self.gfx_latest = []

		op = self.prev_operation()
		flip = self.flipped_operation(op)

		if op:
			flip = self.flipped_operation(op)
			self.execute_operation(op)
			self.action_queue.insert(0,flip)	


	def execute_operation(self, op):
		if op[0] =='swap':
			self.original[op[1]], self.original[op[2]] = self.original[op[2]], self.original[op[1]]
			a = self.gfx_rectangles[op[1]]
			b = self.gfx_rectangles[op[2]]
			acoords = self.canvas.coords(a)
			bcoords = self.canvas.coords(b)
			self.canvas.coords(a,bcoords[0],acoords[1],bcoords[2],acoords[3])
			self.canvas.coords(b,acoords[0],bcoords[1],acoords[2],bcoords[3])
			self.gfx_rectangles[op[1]], self.gfx_rectangles[op[2]] = self.gfx_rectangles[op[2]], self.gfx_rectangles[op[1]]
			self.canvas.itemconfig(a, fill=self.gfx_defaultcolor)
			self.canvas.itemconfig(b, fill=self.gfx_defaultcolor)
			self.gfx_latest.append(a)
			self.gfx_latest.append(b)

		elif op[0]=='color':
			item = self.gfx_rectangles[op[1]]
			self.canvas.itemconfig(item, fill=op[2])

		elif op[0]=='decolor':
			item = self.gfx_rectangles[op[1]]
			self.canvas.itemconfig(item, fill=self.gfx_defaultnocolor)

		elif op[0]=='separate':
			x = self.gfx_windowmargin + self.gfx_left + op[1]*self.gfx_rectwidth
			line = self.canvas.create_line(x,self.gfx_top,x,self.gfx_bottom, fill=op[2], width=op[3], tags="all")
			self.gfx_separators.append((op[1], line))

		elif op[0]=='deseparate':
			i = len(self.gfx_separators)-1
			while i>=0:
				if (self.gfx_separators[i])[0]==op[1]:
					self.canvas.delete((self.gfx_separators[i])[1])
					self.gfx_separators.remove(self.gfx_separators[i])
					break
				i -= 1

		else:
			self.original[op[0]] = op[1]
			item = self.gfx_rectangles[op[0]]
			value = self.data[op[0]]
			coords = self.canvas.coords(item)
			self.canvas.coords(item,coords[0],coords[1],coords[2],self.gfx_windowmargin + self.gfx_top + value*self.gfx_scale)
			self.canvas.itemconfig(item, fill=self.gfx_defaultcolor)
			self.gfx_latest.append(item)


	def flipped_operation(self, op):
		flip = op

		if op:
			if not isinstance(op[0], int):
				if op[0]=='separate':
					flip = ['deseparate', op[1]]

				elif op[0]=='deseparate':
					flip = ['separate', op[1]]
					i = len(self.gfx_separators)-1
					while i>=0:
						item = (self.gfx_separators[i])
						if item[0] == op[1]:
							color = self.canvas.itemcget(item[1], 'fill')
							width = self.canvas.itemcget(item[1], 'width')
							flip.append(color)
							flip.append(width)
							break
						i -= 1

				elif op[0]=='color':
					flip = ['decolor', op[1]]

				elif op[0]=='decolor':
					flip = ['color', op[1]]
					item = self.gfx_rectangles[op[1]]
					color = self.canvas.itemcget(item, 'fill')
					flip.append(color)

				elif op[0]=='swap':
					# Do nothing
					None

			else:
				flip[1] = self.original[flip[0]]
		
		return flip
