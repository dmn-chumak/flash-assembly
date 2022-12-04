function FlashCanvas(stage, width, height) {
    let _buffers    = [ ];
    let _attributes = [ ];
    let _uniforms   = [ ];
    let _programs   = [ ];
    let _shaders    = [ ];
    let _textures   = [ ];

    let _runtime    = null;
    let _wrapper    = null;
    let _canvas     = null;
    let _context    = null;

    this.createBuffer = function() {
        return _buffers.push(_context.createBuffer()) - 1;
    };
    this.deleteBuffer = function(bufferID) {
        _context.deleteBuffer(_buffers[bufferID]);
        _buffers[bufferID] = null;
    };
    this.bindBuffer = function(target, bufferID) {
        _context.bindBuffer(target, _buffers[bufferID]);
    };
    this.bufferData = function(target, bufferPtr, bufferLen, usage) {
        if (bufferPtr != 0) {
            _context.bufferData(target, _runtime.readBuffer(Int8Array, bufferPtr, bufferLen), usage);
        } else {
            _context.bufferData(target, bufferLen, usage);
        }
    };
    this.bufferSubData = function(target, offset, bufferPtr, bufferLen) {
        _context.bufferSubData(target, offset, _runtime.readBuffer(Int8Array, bufferPtr, bufferLen));
    };

    this.createRenderBuffer = function() {
        return _buffers.push(_context.createRenderbuffer()) - 1;
    };
    this.deleteRenderBuffer = function(bufferID) {
        _context.deleteRenderbuffer(_buffers[bufferID]);
        _buffers[bufferID] = null;
    };
    this.bindRenderBuffer = function(target, bufferID) {
        _context.bindRenderbuffer(target, _buffers[bufferID]);
    };
    this.renderBufferStorage = function(target, format, width, height) {
        _context.renderbufferStorage(target, format, width, height);
    };

    this.createFrameBuffer = function() {
        return _buffers.push(_context.createFramebuffer()) - 1;
    };
    this.deleteFrameBuffer = function(bufferID) {
        _context.deleteFramebuffer(_buffers[bufferID]);
        _buffers[bufferID] = null;
    };
    this.bindFrameBuffer = function(target, bufferID) {
        _context.bindFramebuffer(target, _buffers[bufferID]);
    };
    this.checkFrameBufferStatus = function(target) {
        return _context.checkFramebufferStatus(target);
    };
    this.frameBufferRenderBuffer = function(target, attachment, bufferTarget, bufferID) {
        _context.framebufferRenderbuffer(target, attachment, bufferTarget, _buffers[bufferID]);
    };
    this.frameBufferTexture2D = function(target, attachment, textureTarget, textureID, mipLevel) {
        _context.framebufferTexture2D(target, attachment, textureTarget, _textures[textureID], mipLevel);
    };
    this.readPixels = function(x, y, width, height, format, type, bufferPtr, bufferLen) {
        _context.readPixels(x, y, width, height, format, type, _runtime.readBuffer(Int8Array, bufferPtr, bufferLen));
    };

    this.createProgram = function() {
        return _programs.push(_context.createProgram()) - 1;
    };
    this.deleteProgram = function(programID) {
        _context.deleteProgram(_programs[programID]);
        _programs[programID] = null;
    };
    this.validateProgram = function(programID) {
        _context.validateProgram(_programs[programID]);
    };
    this.linkProgram = function(programID) {
        _context.linkProgram(_programs[programID]);
    };
    this.checkProgramStatus = function(programID) {
        return (_context.getProgramParameter(_programs[programID], _context.LINK_STATUS).length == 0);
    };
    this.useProgram = function(programID) {
        _context.useProgram(_programs[programID]);
    };

    this.createShader = function(type) {
        return _shaders.push(_context.createShader(type)) - 1;
    };
    this.deleteShader = function(shaderID) {
        _context.deleteShader(_shaders[shaderID]);
        _shaders[shaderID] = null;
    };
    this.shaderSource = function(shaderID, programPtr, programLen) {
        _context.shaderSource(_shaders[shaderID], _runtime.readString(programPtr, programLen));
    };
    this.compileShader = function(shaderID) {
        _context.compileShader(_shaders[shaderID]);
    };
    this.attachShader = function(programID, shaderID) {
        _context.attachShader(_programs[programID], _shaders[shaderID]);
    };
    this.detachShader = function(programID, shaderID) {
        _context.detachShader(_programs[programID], _shaders[shaderID]);
    };
    this.checkShaderStatus = function(shaderID) {
        return (_context.getShaderParameter(_shaders[shaderID], _context.COMPILE_STATUS).length == 0);
    };

    this.createTexture = function() {
        return _textures.push(_context.createTexture()) - 1;
    };
    this.deleteTexture = function(textureID) {
        _context.deleteTexture(_textures[textureID]);
        _textures[textureID] = null;
    };
    this.bindTexture = function(target, textureID) {
        _context.bindTexture(target, _textures[textureID]);
    };
    this.activeTexture = function(textureUnit) {
        _context.activeTexture(textureUnit);
    };
    this.copyTexImage2D = function(target, mipLevel, x, y, width, height) {
        _context.copyTexImage2D(target, mipLevel, _context.RGBA, x, y, width, height, 0);
    };
    this.copyTexSubImage2D = function(target, mipLevel, offsetX, offsetY, x, y, width, height) {
        _context.copyTexSubImage2D(target, mipLevel, offsetX, offsetY, x, y, width, height);
    };
    this.texParameterI = function(target, parameter, value) {
        _context.texParameteri(target, parameter, value);
    };
    this.texParameterF = function(target, parameter, value) {
        _context.texParameterf(target, parameter, value);
    };
    this.texImage2D = function(target, mipLevel, width, height, bufferPtr, bufferLen) {
        if (bufferPtr != 0) {
            _context.texImage2D(target, mipLevel, _context.RGBA, width, height, 0, _context.RGBA, _context.UNSIGNED_BYTE, _runtime.readBuffer(Uint8Array, bufferPtr, bufferLen));
        } else {
            _context.texImage2D(target, mipLevel, _context.RGBA, width, height, 0, _context.RGBA, _context.UNSIGNED_BYTE, null);
        }
    };
    this.texSubImage2D = function(target, mipLevel, offsetX, offsetY, width, height, format, bufferPtr, bufferLen) {
        _context.texSubImage2D(target, mipLevel, offsetX, offsetY, width, height, _context.RGB, _context.UNSIGNED_BYTE, _runtime.readBuffer(Uint8Array, bufferPtr, bufferLen));
    };
    this.generateMipmap = function(target) {
        _context.generateMipmap(target);
    };
    this.pixelStoreI = function(param, value) {
        _context.pixelStorei(param, value);
    };

    this.getUniformLocation = function(programID, namePtr, nameLen) {
        return _uniforms.push(_context.getUniformLocation(_programs[programID], _runtime.readString(namePtr, nameLen))) - 1;
    };
    this.uniform1I = function(uniformID, x) {
        _context.uniform1i(_uniforms[uniformID], x);
    };
    this.uniform2I = function(uniformID, x, y) {
        _context.uniform2i(_uniforms[uniformID], x, y);
    };
    this.uniform3I = function(uniformID, x, y, z) {
        _context.uniform3i(_uniforms[uniformID], x, y, z);
    };
    this.uniform4I = function(uniformID, x, y, z, w) {
        _context.uniform4i(_uniforms[uniformID], x, y, z, w);
    };
    this.uniformVI = function(uniformID, bufferPtr, bufferLen) {
        _context.uniform4iv(_uniforms[uniformID], _runtime.readBuffer(Int32Array, bufferPtr, bufferLen / 4));
    };
    this.uniform1F = function(uniformID, x) {
        _context.uniform1f(_uniforms[uniformID], x);
    };
    this.uniform2F = function(uniformID, x, y) {
        _context.uniform2f(_uniforms[uniformID], x, y);
    };
    this.uniform3F = function(uniformID, x, y, z) {
        _context.uniform3f(_uniforms[uniformID], x, y, z);
    };
    this.uniform4F = function(uniformID, x, y, z, w) {
        _context.uniform4f(_uniforms[uniformID], x, y, z, w);
    };
    this.uniformVF = function(uniformID, bufferPtr, bufferLen) {
        _context.uniform4fv(_uniforms[uniformID], _runtime.readBuffer(Float32Array, bufferPtr, bufferLen / 4));
    };
    this.uniformMatrixVF = function(uniformID, bufferPtr, bufferLen) {
        _context.uniformMatrix4fv(_uniforms[uniformID], false, _runtime.readBuffer(Float32Array, bufferPtr, bufferLen / 4));
    };

    this.getAttribLocation = function(programID, namePtr, nameLen) {
        return _attributes.push(_context.getAttribLocation(_programs[programID], _runtime.readString(namePtr, nameLen))) - 1;
    };
    this.vertexAttribPointer = function(attributeID, size, type, stride, offset) {
        _context.vertexAttribPointer(_attributes[attributeID], size, type, false, stride, offset);
    };
    this.vertexAttrib1F = function(attributeID, x) {
        _context.vertexAttrib1f(_attributes[attributeID], x);
    };
    this.vertexAttrib2F = function(attributeID, x, y) {
        _context.vertexAttrib2f(_attributes[attributeID], x, y);
    };
    this.vertexAttrib3F = function(attributeID, x, y, z) {
        _context.vertexAttrib3f(_attributes[attributeID], x, y, z);
    };
    this.vertexAttrib4F = function(attributeID, x, y, z, w) {
        _context.vertexAttrib4f(_attributes[attributeID], x, y, z, w);
    };
    this.vertexAttribVF = function(attributeID, bufferPtr, bufferLen) {
        _context.vertexAttrib4fv(_attributes[attributeID], _runtime.readBuffer(Float32Array, bufferPtr, bufferLen / 4));
    };
    this.enableVertexAttribArray = function(attributeID) {
        _context.enableVertexAttribArray(_attributes[attributeID]);
    };
    this.disableVertexAttribArray = function(attributeID) {
        _context.disableVertexAttribArray(_attributes[attributeID]);
    };

    this.cullFace = function(mode) {
        _context.cullFace(mode);
    };
    this.frontFace = function(mode) {
        _context.frontFace(mode);
    };

    this.blendColor = function(red, green, blue, alpha) {
        _context.blendColor(red, green, blue, alpha);
    };
    this.blendEquation = function(mode) {
        _context.blendEquation(mode);
    };
    this.blendEquationSeparate = function(modeRGB, modeAlpha) {
        _context.blendEquationSeparate(modeRGB, modeAlpha);
    };
    this.blendFunc = function(srcFactor, dstFactor) {
        _context.blendFunc(srcFactor, dstFactor);
    };
    this.blendFuncSeparate = function(srcFactorRGB, dstFactorRGB, srcFactorAlpha, dstFactorAlpha) {
        _context.blendFuncSeparate(srcFactorRGB, dstFactorRGB, srcFactorAlpha, dstFactorAlpha);
    };

    this.stencilFunc = function(compareMode, reference, mask) {
        _context.stencilFunc(compareMode, reference, mask);
    };
    this.stencilFuncSeparate = function(cullingMode, compareMode, reference, mask) {
        _context.stencilFuncSeparate(cullingMode, compareMode, reference, mask);
    };
    this.stencilMask = function(mask) {
        _context.stencilMask(mask);
    };
    this.stencilMaskSeparate = function(cullingMode, mask) {
        _context.stencilMaskSeparate(cullingMode, mask);
    };
    this.stencilOp = function(stencilFail, depthFail, bothPass) {
        _context.stencilOp(stencilFail, depthFail, bothPass);
    };
    this.stencilOpSeparate = function(cullingMode, stencilFail, depthFail, bothPass) {
        _context.stencilOpSeparate(cullingMode, stencilFail, depthFail, bothPass);
    };

    this.depthFunc = function(compareMode) {
        _context.depthFunc(compareMode);
    };
    this.depthMask = function(enable) {
        _context.depthMask(enable);
    };
    this.depthRange = function(nearValue, farValue) {
        _context.depthRange(nearValue, farValue);
    };

    this.scissor = function(x, y, width, height) {
        _context.scissor(x, y, width, height);
    };
    this.viewport = function(x, y, width, height) {
        _context.viewport(x, y, width, height);
    };
    this.clearColor = function(red, green, blue, alpha) {
        _context.clearColor(red, green, blue, alpha);
    };
    this.clearStencil = function(stencil) {
        _context.clearStencil(stencil);
    };
    this.clearDepth = function(depth) {
        _context.clearDepth(depth);
    };
    this.colorMask = function(red, green, blue, alpha) {
        _context.colorMask(red, green, blue, alpha);
    };
    this.enable = function(capability) {
        _context.enable(capability);
    };
    this.disable = function(capability) {
        _context.disable(capability);
    };
    this.clear = function(mask) {
        _context.clear(mask);
    };
    this.drawArrays = function(renderMode, first, count) {
        _context.drawArrays(renderMode, first, count);
    };
    this.drawElements = function(renderMode, count, type, offset) {
        _context.drawElements(renderMode, count, type, offset);
    };
    this.finish = function() {
        _context.finish();
    };
    this.flush = function() {
        _context.flush();
    };

    this.compose = function(runtime) {
        _runtime = runtime;

        _canvas = document.createElement('canvas');
        _canvas.style.visibility = 'visible';
        _canvas.width = width;
        _canvas.height = height;

        let config = {
            alpha:      true,
            antialias:  true,
            depth:      true,
            stencil:    true
        };

        _wrapper = document.getElementById(stage);
        _context = _canvas.getContext('webgl', config);
        _wrapper.appendChild(_canvas);
    };
    this.dispose = function() {
        _wrapper.removeChild(_canvas);
        _wrapper = null;
        _canvas = _context = null;
    };
    this.context = function() {
        return _canvas;
    };

    return this;
}
