<script lang="ts">
import { defineComponent } from 'vue';
import Folder from './MyFiles_Components/Folder.vue'
//import tree from './MyFiles_Components/testFileTree.json'
import {Types} from '../types'
export default defineComponent ({
        components: {
            Folder
        },
        methods: {
            constructFileTree() {
                //return new Types.Folder("root", [new Types.Folder("Folder1", [], [new Types.Item("File2", "20MB")])], [new Types.Item("File1", "3GB")])
                return new Types.Folder("root", [], [new Types.Item("file", "csv", 
`1,2,3,4
5,6,7,8`
                )])
            }
        }
    })
</script>

<template>
    <h2>My Files Menu</h2>
    <Folder :folder="constructFileTree()" />
</template>