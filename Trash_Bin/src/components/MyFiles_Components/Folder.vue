<script lang="ts">
import { defineComponent } from 'vue';
import {Types} from '../../types'
import Item from './Item.vue'
import DeleteButton from '../General_Components/DeleteButton.vue'
import AddButton from '../General_Components/AddButton.vue';
    export default defineComponent ({
        props: {
            folder: Types.Folder
        },
        data() {return {
            isOpen: false
        }},
        components: {
            Item,
            DeleteButton,
            AddButton
        },
        emits: ['delete'],
        methods: {
            deleteItem(currItem: Types.Item) {
                if(this.folder != null) {
                    this.folder.items = this.folder.items.filter((item) => item != currItem)
                    this.$forceUpdate();
                }
            },
            deleteFolder(currFolder: Types.Folder) {
                if(this.folder != null) {
                    this.folder.folders = this.folder.folders.filter((folder) => folder != currFolder)
                    this.$forceUpdate();
                }
            },
            addFolder(currFolder: Types.Folder) {
                if(this.folder != null) {
                    this.folder.folders.push(new Types.Folder("New Folder", [], [], true))
                    this.isOpen = true
                    this.$forceUpdate()
                }
            },
            nameFolder() {
                if (this.folder != null) {
                    this.folder.isNew = false
                    this.$forceUpdate()
                }
            }
        }
    })
</script>

<template>
    <div>
        <span v-if="!folder?.isNew" @click="() => isOpen = !isOpen">
            <span v-if="!isOpen">📁</span>
            <span v-if="isOpen">📂</span>
            Name: {{ folder?.name }}
        </span>
        <span v-else>
            📁<input v-model="folder.name" @keyup.enter="nameFolder"/>
        </span>
        <AddButton @click="addFolder"/>
        <DeleteButton @click="$emit('delete')" />
        <Item v-for="currItem in folder?.items" v-if="isOpen" :item="currItem" @delete="deleteItem(currItem)" />
        <Folder v-for="currFolder in folder?.folders" v-if="isOpen" :folder="currFolder" @delete="deleteFolder(currFolder)" />  
    </div>
</template>

<style>

</style>