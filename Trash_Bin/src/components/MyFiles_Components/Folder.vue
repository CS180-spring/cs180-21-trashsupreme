<script lang="ts">
import { defineComponent } from 'vue';
import {Types} from '../../types'
import Item from './Item.vue'
import DeleteButton from '../General_Components/DeleteButton.vue'
import AddButton from '../General_Components/AddButton.vue'
import UploadButton from '../General_Components/UploadButton.vue'
import { input, badge, oval_button } from '@/tailwindClasses';
import {sendCreate, sendCreateFolder, sendDelete, sendDeleteFolder} from '../../requests'
    
    export default defineComponent ({
        props: {
            folder: Types.Folder
        },
        data() {return {
            input, badge, oval_button,
            isOpen: false,
            hasUpload: false,
            file: Blob,
            padding: (this.folder != undefined) ? this.folder.depth * 30 + "px" : "0px"
        }},
        components: {
            Item,
            DeleteButton,
            AddButton,
            UploadButton
        },
        emits: ['delete', 'upload'],
        methods: {
            getItem(event: any) {
                this.file = event.target.files[0]
            },
            addItem() {
                let content: string;
                let getExtention = this.file.name.match(/\.[^.]*$/gi)
                let extention = ''
                if (getExtention != null) {
                    extention = getExtention[0]
                    extention = extention.slice(-(extention.length - 1))
                    console.log(extention)
                }
                if (typeof this.file == 'object') {
                    const Reader = new FileReader()
                        Reader.onload = (res) => {
                            if (res.target != null && typeof res.target.result == 'string') {
                                content = res.target.result
                                if (this.folder != undefined) {
                                    let item = new Types.Item(this.file.name, extention, content, '-1', this.folder.depth + 1)
                                    let upload = sendCreate(item, this.folder)
                                    upload.then((res) => {
                                        item.docID = res
                                        if (this.folder != undefined) this.folder.items.push(item)
                                        this.hasUpload = false
                                    })
                                    upload.catch((err) => {
                                        console.log(err)
                                        if (this.folder != undefined) this.folder.items.push(item) //DEBUG Remove once HTTP request works
                                    })
                                }
                            }
                        }
                        Reader.readAsText(this.file)
                }
                this.$forceUpdate()
            },
            deleteItem(currItem: Types.Item) {
                let upload = sendDelete(currItem)
                upload.then(() => {
                    if (this.folder != null) {
                        this.folder.items = this.folder.items.filter((item) => item != currItem)
                    }
                })
                this.$forceUpdate();
            },
            deleteFolder(currFolder: Types.Folder) {
                let upload = sendDeleteFolder(currFolder)
                upload.then(() => {
                    if(this.folder != null) {
                        this.folder.folders = this.folder.folders.filter((folder) => folder != currFolder)
                        this.$forceUpdate();
                    }
                })
            },
            addFolder(currFolder: Types.Folder) {
                if(this.folder != null) {
                    this.folder.folders.push(new Types.Folder("New Folder", [], [], true, this.folder.depth + 1))
                    this.isOpen = true
                    this.$forceUpdate()
                }
                
            },
            nameFolder() {
                this.$emit('upload')
            },
            submitNewFolder(folder: Types.Folder) {
                let upload = sendCreateFolder(folder, this.folder)
                upload.then(() =>  {
                    if (folder != null) {
                        folder.isNew = false
                        // this.folder.nodeID = upload
                        this.$forceUpdate()
                    }
                })
            }
        }
    })
</script>

<template>
    <div :style="{'padding-left':padding}">
        <span :class=badge>
            <span v-if="!folder?.isNew" @click="() => isOpen = !isOpen">
                <span v-if="!isOpen">📁</span>
            <span v-if="isOpen">📂</span>
            Name: {{ folder?.name }}
            </span>
            <span v-else>
                📁<input :class=input v-model="folder.name" @keyup.enter="nameFolder"/>
            </span>
            <span v-if="folder?.name != 'Search' && !folder?.isNew">
                <AddButton @click="addFolder"/>
                <DeleteButton @click="$emit('delete')" />
                <UploadButton @click="hasUpload = !hasUpload"/>
            </span>
        </span>
        <div v-if="hasUpload">
            <input type="file" ref="file" accept=".csv, .tsv, .txt, .json" @change="getItem"/>
            <button :class=oval_button @click="addItem">Submit</button>
        </div>
        <Item v-for="currItem in folder?.items" v-if="isOpen" :item="currItem" @delete="deleteItem(currItem)"/>
        <Folder v-for="currFolder in folder?.folders" v-if="isOpen" :folder="currFolder" @delete="deleteFolder(currFolder)" @upload="submitNewFolder(currFolder)" />  
    </div>
</template>

<style>

</style>