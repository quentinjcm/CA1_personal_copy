class Triangle:
	def __init__(self, _v0, _v1, _v2, _n0, _n1, _n2, _uv0, _uv1, _uv2):
		self.v0 = _v0
		self.v1 = _v1
		self.v2 = _v2
		self.n0 = _n0
		self.n1 = _n1
		self.n2 = _n2
		self.uv0 = _uv0
		self.uv1 = _uv1
		self.uv2 = _uv2

class rtParse:
	def __init__(self, _file_in, _file_out):
		self.file_in = open(_file_in, "r")
		self.file_out = open(_file_out, "w")
		self.verts = []
		self.normals = []
		self.uvs = []
		self.tris = []

	def runParser(self):
		self.getVerts()
		self.getNormals()
		i = 0
		for n in self.normals:
			print i, n
			i+=1
		self.getTris()
		self.getUVs()
		self.writeToFile()
		self.file_in.close()
		self.file_out.close()

	def getVerts(self):
		self.file_in.seek(0)
		for i in self.file_in:
			if "v " in i:
				split = i.split()
				vert = (split[1], split[2], split[3])
				self.verts.append(vert)
		print "vertex list length: ", len(self.verts)

	def getNormals(self):
		self.file_in.seek(0)
		for i in self.file_in:
			if "vn" in i:
				split  = i.split()
				norm = (split[1], split[2], split[3])
				self.normals.append(norm)
		print "normal list length: ", len(self.normals)

	def getUVs(self):
		self.file_in.seek(0)
		for i in self.file_in:
			if "vt" in i:
				split = i.split()
				uv = (split[1], split[2])
				self.uvs.append(uv)

	def getTris(self):
		self.file_in.seek(0)
		for i in self.file_in:
			if "f " in i:
				split = i.split()
				sect_0 = split[1].split("/")
				sect_1 = split[2].split("/")
				sect_2 = split[3].split("/")

				vert_0 = int(sect_0[0])-1
				vert_1 = int(sect_1[0])-1
				vert_2 = int(sect_2[0])-1

				norm_0 = int(sect_0[2])-1
				norm_1 = int(sect_1[2])-1
				norm_2 = int(sect_2[2])-1

				uv_0 = int(sect_0[1])-1
				uv_1 = int(sect_1[1])-1
				uv_2 = int(sect_2[1])-1

				tri = Triangle(vert_0, vert_1, vert_2, norm_0, norm_1, norm_2, uv_0, uv_1, uv_2)
				self.tris.append(tri)

	def writeTri(self, tri_id, tri):
		self.file_out.write("\tngl::Vec3 t" + tri_id + "v0(" + self.verts[tri.v0][0] + "," + \
			 									 			   self.verts[tri.v0][1] + "," + \
			 												   self.verts[tri.v0][2] + ");\n" )
		self.file_out.write("\tngl::Vec3 t" + tri_id + "v1(" + self.verts[tri.v1][0] + "," + \
			 												   self.verts[tri.v1][1] + "," + \
			 												   self.verts[tri.v1][2] + ");\n" )
		self.file_out.write("\tngl::Vec3 t" + tri_id + "v2(" + self.verts[tri.v2][0] + "," + \
			 												   self.verts[tri.v2][1] + "," + \
			 												   self.verts[tri.v2][2] + ");\n" )
		self.file_out.write("\tngl::Vec3 t" + tri_id + "n0(" + self.normals[tri.n0][0] + "," + \
			 									 			   self.normals[tri.n0][1] + "," + \
			 												   self.normals[tri.n0][2] + ");\n" )
		self.file_out.write("\tngl::Vec3 t" + tri_id + "n1(" + self.normals[tri.n1][0] + "," + \
			 												   self.normals[tri.n1][1] + "," + \
			 												   self.normals[tri.n1][2] + ");\n" )
		self.file_out.write("\tngl::Vec3 t" + tri_id + "n2(" + self.normals[tri.n2][0] + "," + \
			 												   self.normals[tri.n2][1] + "," + \
			 												   self.normals[tri.n2][2] + ");\n" )

		self.file_out.write("\tngl::Vec2 t" + tri_id + "uv0(" + self.uvs[tri.uv0][0] + "," + \
			 												    self.uvs[tri.uv0][1] + ");\n" )
		self.file_out.write("\tngl::Vec2 t" + tri_id + "uv1(" + self.uvs[tri.uv1][0] + "," + \
			 												    self.uvs[tri.uv1][1] + ");\n" )
		self.file_out.write("\tngl::Vec2 t" + tri_id + "uv2(" + self.uvs[tri.uv2][0] + "," + \
			 												    self.uvs[tri.uv2][1] + ");\n" )

		self.file_out.write("\tTriangle t" + tri_id + "(t" + tri_id + "v0, t" + tri_id + "v1, t" + tri_id + "v2, t" + tri_id + "n0, t" + tri_id + "n1, t" + tri_id + "n2, t" + tri_id + "uv0, t" + tri_id + "uv1, t"+ tri_id + "uv2);\n")
		self.file_out.write("\tmeshOut->addTri(t" + str(tri_id) + ");\n")

	def writeToFile(self):
		self.file_out.write("std::shared_ptr<TriangleMesh> Meshes::scene1()\n{\n")
		self.file_out.write("\tauto meshOut = std::make_shared<TriangleMesh>();\n")
		tri_id = 0
		for tri in self.tris:
			tri_id += 1
			self.writeTri(str(tri_id), tri)
		self.file_out.write("\treturn meshOut;\n}")


a = rtParse("sphere3.obj", "sphere3.txt")
a.runParser()
